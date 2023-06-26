import numpy as np

input = np.array([0, 1, 10, 20, 31, 21, 29, 30,
          32, 41, 12, 13, 15, 15, 14, 12,
          54, 65, 43, 32, 12, 43, 12, 43,
          54, 64, 43, 31, 11, 21, 32, 44])

output = np.fft.rfft(input)
print(output)