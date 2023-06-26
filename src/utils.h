//
// Created by wedo on 2023/6/25.
//

#ifndef ARRAYMICROPHONES_UTILS_H
#define ARRAYMICROPHONES_UTILS_H

#include <vector>
#include <cstddef>
#include <ctime>

#define GetElapsedTime(...) ({ \
    timespec _start{}, _end{}; \
    clock_gettime(CLOCK_REALTIME, &_start); \
    __VA_ARGS__;                             \
    clock_gettime(CLOCK_REALTIME, &_end); \
    auto _elapsed = (double) (_end.tv_sec - _start.tv_sec) + (_end.tv_nsec - _start.tv_nsec) / 1e9; \
    _elapsed; \
});

std::vector<short> GetRandomData(size_t eleSize, unsigned seed = 0);

void WriteVectorToText(const char *outTxtPath, const float *data, size_t eleSize);

#endif //ARRAYMICROPHONES_UTILS_H
