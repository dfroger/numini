numini
======

numini is a library to read configuration file. I use it for numerical
simulation code.

Install
------------------------

### Using precompiled binary ###

It is recommanded to install numini using [conda](http://conda.pydata.org/)

The package is located [here](https://binstar.org/dfroger/numini)
 
### From source ###

Dependencies are [yaml-cpp](http://code.google.com/p/yaml-cpp/) which itself
depends on [Boost](http://www.boost.org/).

Download the latest release from https://github.com/dfroger/numini/releases

Configure, build, and install:

    cd numini/numini
    ../waf configure
    ../waf build
    ../waf install

Most usefull configure options are `--prefix`, `--yaml-cpp-dir` and `--boost-dir`.  See:

    ../waf configure --help

Configuration file
------------------------

The configuration file is a [YAML](http://www.yaml.org/) file, restricted to
section/variables as in [INI](http://en.wikipedia.org/wiki/INI_file) files.

For example, a **INI** file such as:

    [rectangle]

    width = 11
    height = 10
    position = bottom
    start = [1, 3, 0]

    [line]:

    coords_x0 = 2
    coords_x1 = 1
    coords_y0 = 5
    coords_y1 = -3.5
    properties: [1,2,3]

would be written with **numini** as :

    rectangle:
        width: 11
        height: 10
        position: bottom
        start: [1, 3, 0]

    line:
        coords: {"x0": 2, "x1": 1, "y0": 5, "y1": -3.5}
        properties: [1,2,3]

The supported types are:

    - integer
    - float
    - string
    - boolean
    - custom type (C++ class)

Variable value can be scalar of these types, or homogeneous vector or
homogeneous map.

Features
------------------------

- INI files structure like.
- Dectects wrong section names and wrong variable names.
- Custom types.
- Optional Python interface.
- Unit-tested (see `test/test_nimini.py`).
- Raise error if configuration file does not provide a variable, or use default value.


Example
------------------------

See example in `test` directory.
