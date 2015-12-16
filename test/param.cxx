#include "param.hxx"

#include "numini/node.hxx"

#include <iostream> //tmp

using namespace std;

numini::Reader ini;

/*
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
*/

void
Parameters::read_config_file(std::string filename)
{
    ini.load_file(filename);
    ini.move_to_section("rectangle");
    m_width = ini("width");
    cout << "read_config_file: " << m_width << endl;
    /*
    ini.require_scalar(m_width, "width");
    ini.require_scalar(m_height,"height");
    ini.readopt_scalar(m_position, "position", (string) "top");
    ini.require_scalar(m_start, "start");

    ini.move_to_section("line");
    ini.readopt_map(m_coords,"coords");
    ini.require_vector(m_properties,"properties");

    ini.check_for_unknown_sections();
    ini.check_for_unknown_vars();
    */
}

/*
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
*/

