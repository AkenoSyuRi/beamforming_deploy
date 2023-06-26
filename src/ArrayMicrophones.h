#include "Microphone.h"

class ArrayMicrophones {
    fftwf_complex *enhancedSpecData;
    fftwf_plan plan;
public:
    float *enhancedTimeData;
    std::vector<Microphone> mics;

    explicit ArrayMicrophones(int numMicrophones);

    ~ArrayMicrophones();

    void receiveData();

    void transformAllFft(); // 对所有麦克风接受到的数据进行FFT。
    void reserveFreqBand(int start, int end, int n); // 对第n个麦克风进行带通滤波。
    void setFreqComponent(int n, int k, float factor);

    void bandFilter(); // 对特定频带保留，其余置0

    void angleFilter(int decayAngle);

    void checkFreqValidAndProcess(int i, int k, float thresholdAngle);

    void buildSignal();

    // void beamforming();
};