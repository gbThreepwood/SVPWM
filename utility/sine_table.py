# Script to generate sine wave lookup table

import numpy as np
import matplotlib.pyplot as plt

theta = np.arange(0,2*np.pi,(2*np.pi)/256)
lut = 128*np.sin(theta) + 128

print('const uint8_t sinLUT[] PROGMEM = {')
for i in range(0,255):
    print("{0:#0{1}x}".format(int(lut[i]),4) + ',', end=" ")

    if(i%10 == 0):
        print()

print('}')

plt.plot(theta, lut)
plt.show()
