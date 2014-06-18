from distutils.core import setup, Extension

param = Extension(
         '_param',
         sources = ['param.i',],
         swig_opts = ['-c++',],
         libraries = ['yaml-cpp', 'numini'],
        )

setup(name = 'param',
      ext_modules = [param,],
      py_modules = ['param',],
)
