#pragma once

#include <vector>
#include <fftw3.h>
#include <iostream>

#define N 1024
#define N2 513

class Microphone {

public:
    // constructor/methods declarations
    int micId;
    std::vector<float> rawData;
    fftwf_complex *spectrumData;
    fftwf_plan plan;

    explicit Microphone(int id);

    Microphone(Microphone &&other) noexcept;

    void receiveData(const short *data);

    void transformFft() const;

    void reserveFreqBand(int start, int end) const;

    void setFreqComponent(int k, float factor) const;

    ~Microphone();
};