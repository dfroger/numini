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
    
/// Not used in test, just to show it is possible.
void
Parameters::read_config_file_default_const(std::string filename, int file_version)
{
    ini.load_file(filename);
    ini.move_to_section("rectangle");
    set_width( ini("width", double()) );
    set_height( ini("height", double()) );
    set_position( ini("position", std::string()) );
    set_start( ini("start", Vec3()) );

    ini.move_to_section("line");
    set_coords( ini("coords", s2d()) );
    set_properties( ini("properties", vi()) );

    if (file_version==1) {
        ini.move_to_section("starting");
        set_vstart( ini("vstart", vVec3()) );
    }

    if (file_version==2) {
        ini.move_to_section("starting");
        set_mstart( ini("mstart", s2Vec3()) );
    }

    ini.check_for_unknown_sections();
    ini.check_for_unknown_vars();
}
    
void
Parameters::read_config_file_default_values(std::string filename, int file_version)
{
    ini.load_file(filename);
    ini.move_to_section("rectangle");
    set_width( ini("width", 501.) );
    set_height( ini("height", 502.) );
    set_position( ini("position", (string) "top") );
    set_start( ini("start", Vec3(501,502,503)) );

    ini.move_to_section("line");
    s2d default_coords;
    default_coords["x1"] = -1;
    default_coords["x2"] = -2;
    default_coords["x3"] = -3;
    set_coords( ini("coords", default_coords) );

    vi default_properties;
    default_properties.push_back(4);
    default_properties.push_back(5);
    default_properties.push_back(6);
    set_properties( ini("properties", vi()) );
    
    Vec3 start0;
    start0.set_x(-1);
    start0.set_y( 0);
    start0.set_z( 1);
    
    Vec3 start1;
    start1.set_x(-10);
    start1.set_y(  0);
    start1.set_z( 10);
    
    Vec3 start2;
    start2.set_x(-20);
    start2.set_y(  0);
    start2.set_z( 20);

    if (file_version==1) {
        vVec3 default_vstart;
        default_vstart.push_back(start0);
        default_vstart.push_back(start1);
        default_vstart.push_back(start2);
        ini.move_to_section("starting");
        set_vstart( ini("vstart", default_vstart) );
    }

    if (file_version==2) {
        s2Vec3 default_mstart;
        default_mstart["foo"] = start0;
        default_mstart["bar"] = start0;
        default_mstart["baz"] = start0;
        ini.move_to_section("starting");
        set_mstart( ini("mstart", default_mstart) );
    }

    ini.check_for_unknown_sections();
    ini.check_for_unknown_vars();
}
    
void
Parameters::read_config_file(std::string filename, int file_version)
{
    ini.load_file(filename);
    ini.move_to_section("rectangle");
    set_width( ini("width") );
    set_height( ini("height") );
    set_position( ini("position") );
    set_start( ini("start") );

    ini.move_to_section("line");
    set_coords( ini("coords") );
    set_properties( ini("properties") );

    if (file_version==1) {
        ini.move_to_section("starting");
        set_vstart( ini("vstart" ) );
    }

    if (file_version==2) {
        ini.move_to_section("starting");
        set_mstart( ini("mstart") );
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
