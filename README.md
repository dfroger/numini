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

This example can be found in the `example` directory.

Consider the following input file `config.yaml`:

    rectangle:
        width: 11
        height: 10
        position: bottom
        start: [1, 3, 0]

    line:
        coords: {"x0": 2, "x1": 1, "y0": 5, "y1": -3.5}
        properties: [1,2,3]

The following program parse this file:

    #include "numini.hxx"

    #include <string>
    #include <map>
    #include <iostream>

    using namespace std;

    class Vec3
    {
        public:

        Vec3():
            m_x(0.),
            m_y(0.),
            m_z(0.)
        {}

        Vec3(double x, double y, double z):
            m_x(x),
            m_y(y),
            m_z(z)
        {}
        
        double get_x() const { return m_x;}
        double get_y() const { return m_y;}
        double get_z() const { return m_z;}

        void set_x(double x) {m_x = x;}
        void set_y(double y) {m_y = y;}
        void set_z(double z) {m_z = z;}

        private:
        double m_x, m_y, m_z;
    };


    NumIni ini = NumIni("config.yaml");

    namespace YAML {
        template<>
        struct convert<Vec3> {
            static bool decode(const Node& node, Vec3& rhs) {
                if (!node.IsSequence() || node.size() !=3) {
                    return false;
                }
                rhs.set_x(ini.convert<double>(node[0], "first component"));
                rhs.set_y(ini.convert<double>(node[1], "second component"));
                rhs.set_z(ini.convert<double>(node[2], "third component"));
                return true;
            }
        };
    }

    int main()
    {
        // ========================================================================
        ini.move_to_section("rectangle");

        double width = ini.require_scalar<double>("width");
        double height = ini.require_scalar<double>("height");
        string position = ini.readopt_scalar<string>("position", (string) "top");
        Vec3 start = ini.require_scalar<Vec3>("start");

        // ========================================================================
        ini.move_to_section("line");

        map<string,double> coords_default;
        map<string,double> coords = ini.readopt_map<string,double>("coords",
                                                                   coords_default);
        vector<int> properties = ini.require_vector<int>("properties");

        // ========================================================================
        ini.check_for_unknown_sections();
        ini.check_for_unknown_vars();

        cout << "position: " << position << endl;
        cout << "width: " << width << endl;
        cout << "height: " << height << endl;
        cout << "coords: " << coords.size() << " " << coords.find("y1")->second << endl;
        cout << "properties: " << properties.size() << " " << properties[0] << endl;
        cout << "x, y, z: " << start.get_x() << " " << start.get_y() << " " << start.get_z() << endl;
    }
