#!/usr/bin/python2
import glob
import os
import math

files = glob.glob("*.png")



if len(files)>0:
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
        jpg = filen.replace(".png",".jpg")
        os.system("convert %s %s" % (filen, jpg) )
                    
    
    os.system("mkdir -p raw")
    os.system("rm -f raw/*")
    os.system("mv -f *.png raw/")

print "....badly behaved string replacements..."
index = open("index.html").read()
indexFile = file("index.html","w")

indexFile.write( index.replace(".png",".jpg"))
