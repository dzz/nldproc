import fnmatch
import os

matches = []
for root, dirnames, filenames in os.walk('src'):
    for filename in fnmatch.filter(filenames, '*.cpp'):
        matches.append(os.path.join(root, filename))

CppFiles = matches


buildnum = int(float(open('build_num').read()))
buildnum = buildnum + 1
open('build_num','w').write( str(buildnum) )


open('src/build.h','w').write('#pragma once\nconst unsigned int NLDPROC_BUILDNUM = {0};'.format(buildnum))

env = Environment()
#env.Append(CPPDEFINES=['NLDPROC_BUILDNUM={0}'.format(buildnum)])

env.Program(
        'cli', 
        CppFiles, 
        LIBS=
        [
            'libDSPFilters'
        ], 
        CPPPATH=
        [
            './DSPFilters/include',
            './src/processors',
            './src/test_signals',
            './src/utils',
            './src/'
        ], 
        LIBPATH='.',
        CPPFLAGS="-finline-functions -O3 -Ofast -msse -msse2 -msse3 -msse4 -mtune=intel -mfpmath=sse"
 )

