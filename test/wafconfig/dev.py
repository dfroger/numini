from os.path import abspath, dirname, join

# Path to directory 'config' containing this file.
here = dirname(__file__)

# Path to numini git repository root.
root = abspath(join(here, '..', '..'))

def configure(conf):
    conf.options.conda = True
    conf.options.numini_includes = join(root, 'numini')
    conf.options.numini_libpath = join(root, 'numini', 'build')
    conf.options.python_bindings = True
    conf.options.install_python_path = True
