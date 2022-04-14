from building import *

cwd  =  GetCurrentDir()
path =  [cwd + '/inc']
path += [cwd + '.']

src  =  Glob('src/*.c')
src  += Glob('*.c')

if GetDepend(['SNOWFLAKE_USING_SAMPLES']):
    src += Glob('samples/*.c')

group = DefineGroup('SnowFlake', src, depend = ['PKG_USING_SNOWFLAKE'], CPPPATH = path)

Return('group')
