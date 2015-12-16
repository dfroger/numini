from distutils.core import setup, Extension

param = Extension(
         '_param',
         sources = ['param.i', 'param.cxx'],
         swig_opts = ['-c++',],
         libraries = ['yaml-cpp', 'numini'],
         include_dirs = [
             '../numini',
             '/home/froger/miniconda3/envs/numini/include',
         ],
         library_dirs = [
             '../numini/build',
         ],
        )

setup(name = 'param',
      ext_modules = [param,],
      py_modules = ['param',],
)
