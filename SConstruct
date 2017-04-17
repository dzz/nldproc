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

CPPFILES = []

populate_cpp_matches(CPPFILES, "src")
populate_cpp_matches(CPPFILES, "DSPFilters/source")


env = Environment()

if sys.platform == "linux2":
    CPPFLAGS="-finline-functions -O3 -Ofast -msse -msse2 -msse3 -msse4 -mtune=intel -mfpmath=sse"
if sys.platform == "win32":
    CPPFLAGS=""
    #env.Append(CXXFLAGS = ['/DEBUG'])

env.Program(
        'cli', 
        CPPFILES, 
        CPPPATH=
        [
            './DSPFilters/include',
            './src/processors',
            './src/test_signals',
            './src/utils',
            './src/'
        ], 
        LIBPATH='.',
        CPPFLAGS=CPPFLAGS
 )

