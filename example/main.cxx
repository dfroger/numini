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
