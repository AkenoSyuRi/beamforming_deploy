#include "ArrayMicrophones.h"
#include <cmath>

#define SAMPLE_RATE (32000)
#define SOUND_VELOCITY (343)

ArrayMicrophones::ArrayMicrophones(int numMicrophones) {
    for (int i = 0; i < numMicrophones; i++) {
        mics.emplace_back(i);
    }
    enhancedTimeData = new float[N]{};

    enhancedSpecData = fftwf_alloc_complex(N2);
    plan = fftwf_plan_dft_c2r_1d(N, enhancedSpecData, enhancedTimeData, FFTW_ESTIMATE);
}


void ArrayMicrophones::receiveData() {
    // TODO: 使得mic阵列中的每个mic接受对应的数据
}

void ArrayMicrophones::transformAllFft() {
    for (Microphone &mic: mics) {
        mic.transformFft();
    }
}

void ArrayMicrophones::reserveFreqBand(int start, int end, int n) {
    mics[n].reserveFreqBand(start, end);
}

void ArrayMicrophones::setFreqComponent(int n, int k, float factor) {
    mics[n].setFreqComponent(k, factor);
}

ArrayMicrophones::~ArrayMicrophones() {
    // 清理所有的 Microphone对象
    mics.clear();
    delete[]enhancedTimeData;
    fftwf_free(enhancedSpecData);
    fftwf_destroy_plan(plan);
}

// i 代表第i圈， k代表第k个频点， thresholdAngle代表阈值角度
void ArrayMicrophones::checkFreqValidAndProcess(int i, int k, float thresholdAngle) {
    int lower = (i - 1) * 11 + i;
    int upper = lower + 11;

    auto angle_0 = atan2f(mics[0].spectrumData[k][1], mics[0].spectrumData[k][0]);

    for (int j = lower; j < upper + 1; ++j) {
        auto angle_j = atan2f(mics[j].spectrumData[k][1], mics[j].spectrumData[k][0]);
        if (fabsf(angle_0 - angle_j) > thresholdAngle) {
            for (int l = lower; l < upper + 1; ++l) {
                mics[l].setFreqComponent(k, 0.0f);
            }
            mics[0].setFreqComponent(k, 0.0f);
            return;
        }
    }
}

void ArrayMicrophones::angleFilter(int decayAngle) {
    float redAngle = decayAngle * M_PI / 180;
    float unitFactor = 2 * M_PI * SAMPLE_RATE * sinf(redAngle) * 0.032 / (SOUND_VELOCITY * N);

    for (int k = 0; k < 65; ++k) {
        float thresholdAngle = k * unitFactor;
        checkFreqValidAndProcess(4, k, thresholdAngle);
    }

    for (int k = 65; k < 129; ++k) {
        float thresholdAngle = k * unitFactor;
        checkFreqValidAndProcess(3, k, thresholdAngle);
    }

    for (int k = 129; k < 257; ++k) {
        float thresholdAngle = k * unitFactor;
        checkFreqValidAndProcess(2, k, thresholdAngle);
    }

    for (int k = 257; k < 513; ++k) {
        float thresholdAngle = k * unitFactor;
        checkFreqValidAndProcess(1, k, thresholdAngle);
    }
}

void ArrayMicrophones::buildSignal() {
    for (const auto &mic: mics) {
        for (int i = 0; i < N2; ++i) {
            enhancedSpecData[i][0] += mic.spectrumData[i][0];
            enhancedSpecData[i][1] += mic.spectrumData[i][1];
        }
    }
    fftwf_execute(plan);
}

void ArrayMicrophones::bandFilter() {
    for (int i = 1; i < 13; ++i) {
        reserveFreqBand(257, 512, i);
    }
    for (int i = 13; i < 25; ++i) {
        reserveFreqBand(129, 512, i);
    }
    for (int i = 25; i < 37; ++i) {
        reserveFreqBand(65, 256, i);
    }
    for (int i = 37; i < 49; ++i) {
        reserveFreqBand(0, 128, i);
    }
    for (int i = 49; i < 61; ++i) {
        reserveFreqBand(0, 64, i);
    }
}
