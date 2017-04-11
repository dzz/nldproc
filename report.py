#!/usr/bin/python2

import matplotlib.pyplot as plt
import numpy as np
import sys

plt.rcParams.update({'figure.max_open_warning':0})

print ("[ ~REPORTOMATIC~ ] " )
print ("    .... nice job on " + open("build_num").read())
print ("")

fft_spec = open('output/test.report_fft_lims').read().split("\n");

fft_min = float(fft_spec[0]);
fft_max = float(fft_spec[1]);

time_data = open('output/implicit_time').read().split(" ")

proc_time = float(time_data[0])
test_signal_length = float(time_data[1])


Fs = float( open('output/test.samplerate').read().split(" ")[0] )
dt = 1.0 / Fs

reportfile = open('output/test.reportfile').read()
s = np.fromfile('output/' + reportfile)

#### load input signal (naughty)
inputS = None
try:
    inputS = np.fromfile('output/' + 'input.' + reportfile);
except:
    pass

t = np.arange(0, float(s.size) / Fs, dt)

print("Max Amplitude From Input Signal: %f" % (np.max(np.fabs(s)) ) );
print("Input Data Length (frames): %s" % ( s.size) )

# generate noise:
###nse = np.random.randn(len(t))
###r = np.exp(-t/0.05)
###cnse = np.convolve(nse, r)*dt
###cnse = cnse[:len(t)]

print "         [ ~ pretty graphs ~ ]"
plt.style.use('ggplot')

fig, axes = plt.subplots(nrows=3, ncols=1, figsize=(5.7, 6.8))

# plot time signal:

perf = proc_time / test_signal_length
axes[0].set_title(reportfile+": cpu/input=%f" % perf , size = 12)
axes[0].plot(t, s )
axes[0].set_xlabel("t", size = 8)
axes[0].set_ylabel("amp", size = 8)
#axes[0].set_ylim([-1.0,1.0]);

#axes[1].set_title("FFT / 256", size = 11)
axes[1].specgram(s, NFFT=256, Fs=Fs, scale="dB" )
axes[1].set_ylabel("hz", size = 8)
axes[1].set_ylim([fft_min,fft_max])

#axes[2].set_title("magnitude", size = 11)
axes[2].magnitude_spectrum(s, Fs=Fs, scale="dB" )
axes[2].set_xlabel("hz", size = 8)
axes[2].set_ylabel("dB", size = 8)


##axes[4].set_title("Angle Spectrum")
##axes[4].angle_spectrum(s, Fs=Fs )

fig.tight_layout()
plt.savefig("reports/" + reportfile + ".png", boxinches="tight")


if not inputS is None:
    print("found input...")
    time_normalized = np.zeros( len(s) )
    time_normalized[:len(inputS)] += inputS

    
    transfers = 24
    transfer_skip = int(len(s)/transfers)

    for i in range(0, transfers):
        fig, axes = plt.subplots(nrows=1, ncols=1, figsize=(3.5, 3.5))
        plt.style.use('dark_background')
        plt.clf()
        x = time_normalized[i*transfer_skip:(i*transfer_skip)+transfer_skip:1]
        y = s[i*transfer_skip:(i*transfer_skip)+transfer_skip:1]
        dotsizes = np.logspace(0.2,1.8, len(x))
        print "         [ scatter plotting %i events, %i/%i ]" %(len(x),i+1,transfers)
        plt.scatter(x,y, s=dotsizes)
        transfer_str = ".transfer_%i" % (i)
        plt.savefig("reports/" + reportfile + transfer_str + ".png", dpi=40, boxinches="tight")

