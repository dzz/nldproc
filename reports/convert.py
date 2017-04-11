#!/usr/bin/python2
import glob
import os
import math

files = glob.glob("*.png")

t = 0.0
dT = 3.14 * 2 / float(len(files))

print "."
print " {_-_naughty_-_}"
print "  .... compression..."
print "            .."
print "           ."

for filen in files:
    p = int(4.0*(math.sin(t)+1))
    t = t+dT
    prog = ""
    for i in range(0,p):
        prog = prog + " "
    prog = prog + ".*."
    print prog
    gif = filen.replace(".png",".gif")
    os.system("convert %s %s" % (filen, gif) )
                

os.system("mkdir -p raw")
os.system("rm -f raw/*")
os.system("mv -f *.png raw/")

index = open("index.html").read()
indexFile = file("index.html","w")

indexFile.write( index.replace(".png",".gif"))
