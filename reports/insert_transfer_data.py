#!/usr/bin/python2

import glob
import sys

manifest = open("manifest").read().split("\n")
index = open("index.html").read()

print ""
print "[ X,Y ScatterPlot Injection ]"
print ""

for testdescr in manifest:
    search = "<!--{{"+testdescr+"}}-->"
    transfers = glob.glob(testdescr+".raw.transfer*.png")
    replace = ""
    plt = 0
    for transfer in transfers:
        print transfer
        transfer_str = (testdescr+".raw.transfer_%i.png") % plt
        replace = replace + "<img src='"+transfer_str+"'>"
        plt += 1
        if(plt%4 ==0):
            replace = replace + "<br/>"
    index = index.replace(search,replace) 

index_file = open("index.html","w")
index_file.write(index)





