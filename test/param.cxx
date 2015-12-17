#include "param.hxx"

#include "numini/node.hxx"

using namespace std;

numini::Reader ini;

Vec3::Vec3():
    m_x(0.),
    m_y(0.),
    m_z(0.)
{
}

Vec3::Vec3(double x, double y, double z):
    m_x(x),
    m_y(y),
    m_z(z)
{
}

Parameters::Parameters():
    m_position("top")
{
}
    
void
Parameters::read_config_file(std::string filename)
{
    ini.load_file(filename);
    ini.move_to_section("rectangle");
    set_width( ini("width") );
    set_height( ini("height") );
    if (ini.has("position"))
        set_position( ini("position") );
    set_start( ini("start") );

    ini.move_to_section("line");
    set_coords( ini("coords") );
    set_properties( ini("properties") );

    if (ini.has_section("starting")) {
        ini.move_to_section("starting");
        if (ini.has("vstart")) set_vstart( ini("vstart") );
        if (ini.has("mstart")) set_mstart( ini("mstart") );
    }

    ini.check_for_unknown_sections();
    ini.check_for_unknown_vars();
}

namespace YAML
{

// How to convert a YAML node to a Vec3.
template<>
struct convert<Vec3>
{
    static bool decode(const Node& node, Vec3& rhs)
    {
        if (!node.IsSequence() || node.size() !=3) {
            return false;
        }
        rhs.set_x( ini(node[0], "x") );
        rhs.set_y( ini(node[1], "y") );
        rhs.set_z( ini(node[2], "z") );
        return true;
    }
};

}
