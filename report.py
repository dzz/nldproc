#!/usr/bin/python2

import matplotlib.pyplot as plt
import numpy as np

plt.style.use('grayscale')

Fs = float( open('output.environment').read().split(" ")[0] )

dt = 1.0 / Fs

x = np.fromfile("output_left.raw")

t = np.arange(0, x.size / Fs, dt)

NFFT = 32

ax1 = plt.subplot(211)
plt.plot(t, x)
plt.subplot(212, sharex=ax1)
Pxx, freqs, bins, im = plt.specgram(x, NFFT=NFFT, Fs=Fs, noverlap=25)
plt.show()
