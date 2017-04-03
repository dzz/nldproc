#!/usr/bin/python2

###   import matplotlib.pyplot as plt
###   import numpy as np
###   
###   plt.style.use('grayscale')
###   
###   Fs = float( open('output.environment').read().split(" ")[0] )
###   
###   dt = 1.0 / Fs
###   
###   print(dt)
###   
###   x = np.fromfile("output_left.raw")
###   
###   t = np.arange(0, x.size / Fs, dt)
###   
###   NFFT = int(1024)
###   
###   ax1 = plt.subplot(211)
###   plt.plot(t, x)
###   plt.xlabel('t');
###   plt.ylabel('lin_amp');
###   plt.subplot(212, sharex=ax1)
###   Pxx, freqs, bins, im = plt.specgram(x, NFFT=NFFT, Fs=Fs, noverlap=64, scale = 'dB' , mode = 'magnitude' )
###   plt.xlabel('t');
###   plt.ylabel('hz');
###   axes = plt.gca();
###   plt.show()

import matplotlib.pyplot as plt
import numpy as np

Fs = float( open('output.environment').read().split(" ")[0] )
dt = 1.0 / Fs
s = np.fromfile("oversampled.raw")
t = np.arange(0, float(s.size) / Fs, dt)

print s.size

# generate noise:
###nse = np.random.randn(len(t))
###r = np.exp(-t/0.05)
###cnse = np.convolve(nse, r)*dt
###cnse = cnse[:len(t)]

plt.style.use('grayscale')

fig, axes = plt.subplots(nrows=4, ncols=1, figsize=(7, 7))

# plot time signal:

axes[0].set_title("Signal")
axes[0].plot(t, s )
axes[0].set_xlabel("Time")
axes[0].set_ylabel("Amplitude")

axes[1].set_title("FFT / 128")
axes[1].specgram(s, Fs=Fs, scale="dB",cmap="Greys"  )
axes[1].set_xlabel("Time")
axes[1].set_ylabel("Hz")
axes[1].set_ylim([10,22000])

axes[2].set_title("Magnitude")
axes[2].magnitude_spectrum(s, Fs=Fs, scale="dB" )
axes[2].set_xlabel("Hz")
axes[2].set_ylabel("dB")

axes[3].set_title("Phase Spectrum ")
axes[3].phase_spectrum(s, Fs=Fs )
axes[3].set_xlabel("Frequency")
axes[3].set_ylabel("Phase")

##axes[4].set_title("Angle Spectrum")
##axes[4].angle_spectrum(s, Fs=Fs )


fig.tight_layout()
plt.show()
