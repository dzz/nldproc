#!/usr/bin/python2

import matplotlib.pyplot as plt
import numpy as np
import sys


print ("~~~~~~~")

fft_spec = open('output/test.report_fft_lims').read().split("\n");

fft_min = float(fft_spec[0]);
fft_max = float(fft_spec[1]);

Fs = float( open('output/test.samplerate').read().split(" ")[0] )
dt = 1.0 / Fs

reportfile = open('output/test.reportfile').read()
s = np.fromfile('output/' + reportfile)
t = np.arange(0, float(s.size) / Fs, dt)

print("Max Amplitude From Input Signal: %f" % (np.max(np.fabs(s)) ) );
print("Input Data Length (frames): %s" % ( s.size) )

# generate noise:
###nse = np.random.randn(len(t))
###r = np.exp(-t/0.05)
###cnse = np.convolve(nse, r)*dt
###cnse = cnse[:len(t)]

plt.style.use('ggplot')

fig, axes = plt.subplots(nrows=3, ncols=1, figsize=(7, 7))

# plot time signal:

axes[0].titlesize = 0
axes[0].set_title(reportfile, size = 15)
axes[0].plot(t, s )
axes[0].set_xlabel("t", size = 8)
axes[0].set_ylabel("amp", size = 8)
#axes[0].set_ylim([-1.0,1.0]);

axes[1].set_title("FFT / 256", size = 12)
axes[1].specgram(s, NFFT=256, Fs=Fs, scale="dB",cmap="Greys"  )
axes[1].set_ylabel("hz", size = 8)
axes[1].set_ylim([fft_min,fft_max])

axes[2].set_title("magnitude", size = 12)
axes[2].magnitude_spectrum(s, Fs=Fs, scale="dB" )
axes[2].set_xlabel("hz", size = 8)
axes[2].set_ylabel("dB", size = 8)


##axes[4].set_title("Angle Spectrum")
##axes[4].angle_spectrum(s, Fs=Fs )


fig.tight_layout()

# naughty code 
try:
    if(sys.argv[1]):
        plt.savefig("reports/" + reportfile + ".png", boxinches="tight")
except:
    plt.show()


#report_base = reportfile.split("/")[1];

