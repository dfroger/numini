#include "numini.hxx"

#include <string>
#include <map>
#include <iostream>

using namespace std;

int main()
{
    NumIni ini = NumIni("config.yaml");

    ini.move_to_section("rectangle");
    double width, height;
    string position;
    ini.require_scalar(width, "width");
    ini.require_scalar(height, "height");
    ini.readopt_scalar(position, "position", (string) "top");

    ini.move_to_section("line");
    map<string,double> coords;
    vector<int> properties;
    ini.readopt_map(coords,"coords");
    ini.require_vector(properties,"properties");

    ini.check_for_unknown_sections();

    cout << "position: " << position << endl;
    cout << "width: " << width << endl;
    cout << "height: " << height << endl;
    cout << "coords: " << coords.size() << " " << coords.find("y1")->second << endl;
    cout << "properties: " << properties.size() << " " << properties[0] << endl;

    ini.check_for_unknown_vars();
}
