#include "Microphone.h"
#include <cmath>
#include <fftw3.h>
#include <stdexcept>
#include <cstring>

Microphone::Microphone(int id) : micId(id), rawData(N) {
    //fftwf_init_threads();
    //fftwf_plan_with_nthreads(4);
    spectrumData = fftwf_alloc_complex(N2);
    plan = fftwf_plan_dft_r2c_1d(N, rawData.data(), spectrumData, FFTW_ESTIMATE);
}

Microphone::Microphone(Microphone &&other) noexcept: micId(other.micId), rawData(N) {
    spectrumData = other.spectrumData;
    other.spectrumData = nullptr;

    plan = other.plan;
    other.plan = nullptr;
}

void Microphone::receiveData(const short *data) {
    for (int i = 0; i < N; i++) {
        rawData[i] = float(data[i]) / SHRT_MAX;
    }
}

void Microphone::transformFft() const {
    fftwf_execute(plan);
//    for (int i = 0; i < N2; i++) {
//        spectrumData[i][0] /= N;
//        spectrumData[i][1] /= N;
//    }
}

void Microphone::reserveFreqBand(int start, int end) const {
    int clearStart = 0;
    int clearEnd = start - 1;

    // 先使用memset清零从0到start-1的频点
    memset(spectrumData[clearStart], 0, (clearEnd - clearStart + 1) * sizeof(fftwf_complex));

    // 再使用memset清零从end+1到最后的分量
    int clearCount = N2 - (end + 1);
    memset(spectrumData[end + 1], 0, clearCount * sizeof(fftwf_complex));
}

void Microphone::setFreqComponent(int k, float factor) const {
    if (k < 0 || k >= N2) {
        std::string error = "Index out of bounds";
        throw std::out_of_range(error);
    }
    // 修改频域分量:
    spectrumData[k][0] *= factor;
    spectrumData[k][1] *= factor;
}

Microphone::~Microphone() {
//    std::cout << "destructor(addr of plan): " << plan << ", micId: " << micId << std::endl;
    //fftwf_cleanup_threads();
    fftwf_free(spectrumData);
    fftwf_destroy_plan(plan);
}