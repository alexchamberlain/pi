
from distutils.core import setup, Extension

pi = Extension('_pi',
               sources = ['src/pi.c'],
               include_dirs = ['../lib/linux'],
               extra_objects = ['../lib/linux/libpi.a'])

setup(name='pi',
      version='0.1',
      description='Some routines to aid working with Raspberry Pi images.',
      packages=['pi'],
      ext_modules = [pi])

