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
    
void
Parameters::read_config_file(std::string filename, int file_version)
{
    ini.load_file(filename);
    ini.move_to_section("rectangle");
    set_width( ini("width") );
    set_height( ini("height") );
    set_position( ini("position", (string) "top") );
    set_start( ini("start") );

    ini.move_to_section("line");
    set_coords( ini("coords") );
    set_properties( ini("properties") );

    if (file_version==1) {
        ini.move_to_section("starting");
        set_vstart( ini("vstart") );
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
