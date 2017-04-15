#!/usr/bin/python2

import matplotlib

#matplotlib.use('Agg')

import matplotlib.pyplot as plt
import numpy as np
import sys

plt.rcParams.update({'figure.max_open_warning':0})

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

inputS = None
try:
    inputS = np.fromfile('output/' + 'input.' + reportfile);
except:
    pass

t = np.arange(0, float(s.size) / Fs, dt)

plt.style.use('ggplot')


TESTX = np.linspace(0,2,400)
TESTY = np.sin(TESTX ** 2)

if not inputS is None:
    time_normalized = np.zeros( len(s) )
    time_normalized[:len(inputS)] += inputS

    
    transfers = len(s)/1024
    transfer_skip = int(len(s)/transfers)

    for i in range(0, transfers):

        print "%i / %i" %(i,transfers)

        time = np.linspace( (i*transfer_skip) / Fs, ((i+1)*transfer_skip) / Fs, transfer_skip )
        fig, axes = plt.subplots(3, figsize=(9, 9))

        x = time_normalized[i*transfer_skip:(i*transfer_skip)+transfer_skip:1]
        y = s[i*transfer_skip:(i*transfer_skip)+transfer_skip:1]
        dotsizes = np.linspace(0.2,1.8, len(x))

        axes[0].scatter(x,y, s=dotsizes)
        axes[1].plot(time,x);
        axes[2].plot(time,y);
 
        fig.subplots_adjust(hspace=0);

        transfer_str = ".transfer_%i" % (i)
        plt.savefig("reports/" + reportfile + transfer_str + ".png", dpi=72, boxinches="tight")


