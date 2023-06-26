cmake_minimum_required(VERSION 3.0)
project(ArrayMicrophones)

enable_testing()

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

#find_package( FFTW3 REQUIRED )

#include_directories(/usr/local/Cellar/fftw/3.3.10_1/include)
#link_directories(/usr/local/Cellar/fftw/3.3.10_1/lib)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ArrayMicrophones_test.cpp src/utils.cpp src/utils.h)
target_link_libraries(${PROJECT_NAME} F:/Projects/CLionProjects/cpp_deploy/third-party/fftw3/libfftw3f-3.dll)
target_include_directories(${PROJECT_NAME} PUBLIC ./src third-party/fftw3)

#add_executable(FFT_test FFT_test.cpp)
#target_include_directories(array_microphones PUBLIC third-party/fftw3)
#target_link_libraries(FFT_test  F:/Projects/CLionProjects/cpp_deploy/third-party/fftw3/libfftw3f-3.dll)

#add_executable(Microphone_test Microphone_test.cpp src/Microphone.cpp)
#target_include_directories(Microphone_test PUBLIC src third-party/fftw3)
#target_link_libraries(Microphone_test  F:/Projects/CLionProjects/cpp_deploy/third-party/fftw3/libfftw3f-3.dll)

#add_test(
#        NAME array_microphones_test
#        COMMAND array_microphones
#)
#
#add_test(
#        NAME FFT_test
#        COMMAND FFT_test
#        )