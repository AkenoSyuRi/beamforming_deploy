#include "ArrayMicrophones.h"
#include "utils.h"

int main() {
    const int numMicrophones = 61;
    ArrayMicrophones micArray(numMicrophones);

    for (int i = 0; i < numMicrophones; i++) {
        std::vector<short> data = GetRandomData(N, i);
        micArray.mics[i].receiveData(data.data());
    }


    for (int i = 0; i < 100; ++i) {
        auto elapsed = GetElapsedTime(
                micArray.transformAllFft();

                micArray.bandFilter();

                micArray.angleFilter(60);

                micArray.buildSignal();
        );

        printf("elapsed: %lf\n", elapsed);
    }

    WriteVectorToText("../data/output/time_domain.txt", micArray.enhancedTimeData, N);
    return 0;


}