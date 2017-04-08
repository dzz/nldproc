#!/usr/bin/python2

import glob;
def generateProcessorHeader():
    headers = glob.glob("src/processors/*.h")
    writable_headers = []
    for header in headers:
        header = header.split("src/processors/")[1]
        if(header != "processor.h") and ( header!="processors.h"):
            writable_headers.append( header )
    file = open("src/processors/processors.h", "w")

    file.write('/*from code_generate.py */\n')
    file.write('#pragma once\n')
    file.write('#include "processor.h"\n')
    for header in writable_headers:
        file.write('#include "' + header +'"\n')

   
print(" ~~Code Generation~~ ")
print(" creating processor header...")
generateProcessorHeader()


