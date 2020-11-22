# Script to generate sine wave lookup table
# that includes a third harmonic component
# in order to better utilize the DC-link
# voltage.

import numpy as np
import matplotlib.pyplot as plt

theta = np.arange(0,2*np.pi,(2*np.pi)/256)

amplitude = 128

# The amplitude of the third harmonic component should have
# a value of about 0.167
ha = amplitude*0.167

Ua = amplitude*np.sin(theta)
U3h = ha*np.sin(3*theta)
lut = 128 + amplitude*np.sin(theta) + ha*np.sin(3*theta)

print('const uint8_t sinLUT[] PROGMEM = {')
for i in range(0,255):
    print("{0:#0{1}x}".format(int(lut[i]),4) + ',', end=" ")

    if(i%10 == 0):
        print()

print('}')

plt.plot(theta, lut, theta, Ua, theta, U3h)
plt.show()
