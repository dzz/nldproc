#!/usr/bin/python2


import glob;
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


extraSignals = {};
extraFiles = glob.glob("output/extra_*")

for filen in extraFiles:
    extraSignals[filen] = np.fromfile(filen)

TESTX = np.linspace(0,2,400)
TESTY = np.sin(TESTX ** 2)


def hide_ticks(axes):
    axes.set_xticks([])


if not inputS is None:
    time_normalized = np.zeros( len(s) )
    time_normalized[:len(inputS)] += inputS

    
    #transfers = len(s)/1024
    transfers = 1

    transfer_skip = int(len(s)/transfers)

    for i in range(0, transfers):

        plt.figure(0)
        print "%i / %i" %(i,transfers)

        time = np.linspace( (i*transfer_skip) / Fs, ((i+1)*transfer_skip) / Fs, transfer_skip )
        #fig, axes = plt.subplots(3 + len(extraSignals), figsize=(9+(3*len(extraSignals)), 9))

        x = time_normalized[i*transfer_skip:(i*transfer_skip)+transfer_skip:1]
        y = s[i*transfer_skip:(i*transfer_skip)+transfer_skip:1]
        dotsizes = np.linspace(0.2,1.8, len(x))


        axes = {}
        grid_rows = 2 + len(extraSignals)

        grid_size = ( grid_rows, 2 );

        input_axes = plt.subplot2grid( grid_size ,(0,0) );
        input_axes.set_title("input")
        input_axes.plot(time,x);
        input_axes.set_ylim(-1.5,1.5);
        hide_ticks(input_axes)

        output_axes = plt.subplot2grid( grid_size,(1,0) );
        output_axes.set_title("output")
        output_axes.plot(time,y);
        output_axes.set_ylim(-1.5,1.5);
        hide_ticks(output_axes)

        transfer_axes = plt.subplot2grid( grid_size, (0,1), rowspan = grid_rows );
        transfer_axes.set_title("transfer over %i samples" % (transfer_skip))
        transfer_axes.scatter(x,y, s=dotsizes)
        transfer_axes.set_xlim(-1.5,1.5);
        transfer_axes.set_ylim(-1.5,1.5);

        addtlPlot = 2;
        for key in extraSignals:

            addtlSig = extraSignals[key][i*transfer_skip:(i*transfer_skip)+transfer_skip:1]

            metadata_axes = plt.subplot2grid( grid_size, (addtlPlot, 0) )
            metadata_axes.set_title(key)
            metadata_axes.plot(time,addtlSig)
            metadata_axes.set_ylim(-1.5,1.5)
            if(addtlPlot != (grid_rows -1) ):
                hide_ticks(metadata_axes) 
            else:
                metadata_axes.set_xlabel('seconds')

            addtlPlot = addtlPlot + 1
            

        transfer_str = ".transfer_%i" % (i)
        plt.savefig("reports/" + reportfile + transfer_str + ".png", dpi=72, boxinches="tight")

plt.show();
