#include "Microphone.h"
#include <random>
#include <algorithm>
#include <fftw3.h>

std::vector<short> GetRandomData(size_t eleSize, unsigned seed = 0) {
    std::vector<short> data(eleSize);

    if (seed == 0) {
        seed = std::random_device{}();
    }
    std::mt19937 engine(seed);

    std::uniform_int_distribution<short> dis(-32768, 32767);
    std::generate_n(data.begin(), eleSize, [&]() { return dis(engine); });

    return data;
}

int main() {
    // 创建 Microphone 对象

    std::vector<short> inputData = GetRandomData(N);
    Microphone mic(0);

    // 接收音频数据
    mic.receiveData(inputData.data());

    // 进行 FFT 计算
    mic.transformFft();

    // 修改频域分量
    mic.setFreqComponent(10, 2.0);

    // 清除频域范围内的值
//    mic.reserveFreqBand(0, 10);
    mic.reserveFreqBand(500, 512);

    return 0;
}