import fnmatch
import os
import sys

def populate_cpp_matches(matches, dir):
    for root, dirnames, filenames in os.walk(dir):
        for filename in fnmatch.filter(filenames, '*.cpp'):
            matches.append(os.path.join(root, filename))

def advance_buildnum():
    buildnum = int(float(open('build_num').read()))
    buildnum = buildnum + 1
    open('build_num','w').write( str(buildnum) )
    open('src/build.h','w').write('#pragma once\nconst unsigned int NLDPROC_BUILDNUM = {0};'.format(buildnum))



advance_buildnum();

SourceFiles = []

populate_cpp_matches(SourceFiles, "src")
populate_cpp_matches(SourceFiles, "DSPFilters/source")


env = Environment()

if sys.platform == "linux2":
    #CXXFLAGS="-pg"
    CXXFLAGS="-finline-functions -O3 -Ofast -msse -msse2 -msse3 -msse4 -mtune=intel -mfpmath=sse"
if sys.platform == "win32":
    CXXFLAGS="/EHsc /O2 /Ot /arch:AVX"
    #env.Append(CXXFLAGS = ['/DEBUG'])

env.Program(
        'cli', 
        SourceFiles, 
        CPPPATH=
        [
            './DSPFilters/include',
            './src/processors',
            './src/test_signals',
            './src/utils',
            './src/'
        ], 
        LIBPATH='.',
        CXXFLAGS=CXXFLAGS
 )

