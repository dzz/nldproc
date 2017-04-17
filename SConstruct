import fnmatch
import os
import code_generate


CppFiles = []

def populate_cpp_matches(matches, dir):
    for root, dirnames, filenames in os.walk(dir):
        for filename in fnmatch.filter(filenames, '*.cpp'):
            matches.append(os.path.join(root, filename))

populate_cpp_matches(CppFiles, "src")
populate_cpp_matches(CppFiles, "DSPFilters/source")


buildnum = int(float(open('build_num').read()))
buildnum = buildnum + 1
open('build_num','w').write( str(buildnum) )


open('src/build.h','w').write('#pragma once\nconst unsigned int NLDPROC_BUILDNUM = {0};'.format(buildnum))

env = Environment()
#env.Append(CPPDEFINES=['NLDPROC_BUILDNUM={0}'.format(buildnum)])
#env.Append(CXXFLAGS = ['/DEBUG'])
env.Program(
        'cli', 
        CppFiles, 
        CPPPATH=
        [
            './DSPFilters/include',
            './src/processors',
            './src/test_signals',
            './src/utils',
            './src/'
        ], 
        LIBPATH='.',
        #CPPFLAGS="-finline-functions -O3 -Ofast -msse -msse2 -msse3 -msse4 -mtune=intel -mfpmath=sse"
 )

