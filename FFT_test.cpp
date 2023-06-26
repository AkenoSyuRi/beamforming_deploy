#include <cstdio>
#include <cstring>
#include "third-party/fftw3/fftw3.h"

struct ComplexFloat {
    float re;
    float im;
};

int main() {
    float arr[] = {1, 11, 3, 7, 5, 8, 4, 3};
    const int N = 8;  // Size of input signal
    const int nfft = N / 2 + 1;  // Size of input signal

    // Allocate input and output arrays
    auto *_inblock_Real = fftwf_alloc_real(N);
    auto *_outblock_Real = fftwf_alloc_real(nfft);
    memcpy(_inblock_Real, arr, sizeof(arr));

    auto *_inSpec_Complex = fftwf_alloc_complex(nfft);
    auto _fft_plan = fftwf_plan_dft_r2c_1d(N, _inblock_Real, _inSpec_Complex, FFTW_ESTIMATE);
    auto _ifft_plan = fftwf_plan_dft_c2r_1d(N, _inSpec_Complex, _outblock_Real, FFTW_ESTIMATE);

    fftwf_execute(_fft_plan);

    fftwf_free(_inblock_Real);
    fftwf_free(_outblock_Real);
    fftwf_free(_inSpec_Complex);
    fftwf_destroy_plan(_fft_plan);
    fftwf_destroy_plan(_ifft_plan);
    printf("hello world\n");
    return 0;
}
