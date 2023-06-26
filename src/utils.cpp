//
// Created by wedo on 2023/6/25.
//

#include "utils.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <iostream>

std::vector<short> GetRandomData(size_t eleSize, unsigned seed) {
    std::vector<short> data(eleSize);

    if (seed == 0) {
        seed = std::random_device{}();
    }
    std::mt19937 engine(seed);

    std::uniform_int_distribution<short> dis(-32768, 32767);
    std::generate_n(data.begin(), eleSize, [&]() { return dis(engine); });

    return data;
}

void WriteVectorToText(const char *outTxtPath, const float *data, size_t eleSize) {
    std::ofstream file(outTxtPath, std::ios::out | std::ios::app);
    if (file.is_open()) {
        for (int i = 0; i < eleSize; ++i) {
            file << data[i] << ", ";
//            std::cout << data[i] << ", ";
        }
        file << std::endl;
    }
    file.close();
}
