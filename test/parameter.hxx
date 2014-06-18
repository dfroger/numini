#include "numini.hxx"

#include <string>
#include <map>
#include <iostream>

using namespace std;

NumIni ini = NumIni("config.yaml");

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

class Parameters
{
    public:

    void read_config_file()
    {
        ini.move_to_section("rectangle");
        ini.require_scalar(m_width, "width");
        ini.require_scalar(m_height,"height");
        ini.readopt_scalar(m_position, "position", (string) "top");
        ini.require_scalar(m_start, "start");

        ini.move_to_section("line");
        ini.readopt_map(m_coords,"coords");
        ini.require_vector(m_properties,"properties");

        ini.check_for_unknown_sections();
        ini.check_for_unknown_vars();
    }

    std::string position(){return m_position;}
    double width(){return m_width;}
    double height(){return m_height;}
    std::map<std::string,double> coords(){return m_coords;}
    std::vector<int> properties(){return m_properties;}
    Vec3 start(){return m_start;}

    private:

        std::string m_position;
        double m_width;
        double m_height;
        std::map<std::string,double> m_coords;
        std::vector<int> m_properties;
        Vec3 m_start;
};

namespace YAML
{

template<>
struct convert<Vec3> {
    static bool decode(const Node& node, Vec3& rhs) {
        if (!node.IsSequence() || node.size() !=3) {
            return false;
        }
        double x,y,z;
        ini.convert(x, node[0], "first component");
        ini.convert(y, node[1], "second component");
        ini.convert(z, node[2], "third component");
        rhs.set_x(x);
        rhs.set_y(y);
        rhs.set_z(z);
        return true;
    }
};

}

