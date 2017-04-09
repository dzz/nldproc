#!/usr/bin/python2

import glob;
import sys;


banner = "/*** Generated Code (code_generate.py) ***/\n"
def generateProcessorHeader():
    headers = glob.glob("src/processors/*.h")
    writable_headers = []
    for header in headers:
        header = header.split("src/processors/")[1]
        if(header != "processor.h") and ( header!="processors.h"):
            writable_headers.append( header )
    file = open("src/processors/processors.h", "w")

    file.write(banner)
    file.write('#pragma once\n')
    file.write('#include "processor.h"\n')
    for header in writable_headers:
        print("   - " + header )
        file.write('#include "' + header +'"\n')

def generateTestHeader():
    headers = glob.glob("src/tests/*.h")
    writable_headers = []
    for header in headers:
        header = header.split("src/")[1]
        writable_headers.append(header)

    file = open("src/test_includes.h", "w")

    file.write(banner)
    for header in writable_headers:
        print("   - " + header )
        file.write('#include "' + header +'"\n')
    

def generateTestDefine():
    try:
        if(sys.argv[1]):
            file=open("src/test.h","w")
            file.write(banner)
            file.write('#define NLDPROC_CURRENT_TEST ' + sys.argv[1])
    except:
        pass


   
print("[ Code Generation ]")
print(" configuring processors ...")
generateProcessorHeader()
print(" configuring tests ...")
generateTestHeader()
print(" configuring active test...")
generateTestDefine()
print("(complete)")

