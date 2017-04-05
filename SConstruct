buildnum = int(float(open('build_num').read()))
buildnum = buildnum + 1
open('build_num','w').write( str(buildnum) )


open('src/build.h','w').write('#pragma once\nconst unsigned int NLDPROC_BUILDNUM = {0};'.format(buildnum))

env = Environment()
#env.Append(CPPDEFINES=['NLDPROC_BUILDNUM={0}'.format(buildnum)])

env.Program(
        'nldproc_cliwrap', 
        [
            'src/nldproc_cliwrap.cpp', 
            'src/whitenoise.cpp',
            'src/sine.cpp',
            'src/waveshaper.cpp',
            'src/volume.cpp',
            'src/peakfollower.cpp',
            'src/processor.cpp',
            'src/environment.cpp',
            'src/upmixer.cpp',
            'src/downmixer.cpp',
            'src/pipe.cpp',
            'src/clean_gain.cpp',
            'src/shaped_noise.cpp',
            'src/clone_buffer.cpp',
            'src/add_buffers.cpp'
        ], 
        LIBS=
        [
            'libDSPFilters'
        ], 
        CPPPATH=
        [
            './DSPFilters/include'
        ], 
        LIBPATH='.',
        CPPFLAGS="-Ofast"
 )

