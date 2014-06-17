#include "numini.hxx"

#include <string>
#include <map>
#include <iostream>

using namespace std;

int main()
{
    map<string,double> empty_string_double;
    vector<int> empty_int;

    NumIni ini = NumIni("config.yaml");

    ini.move_to_section("rectangle");
    string position = ini.get_scalar("position",(string) "top");
    double width = ini.get_scalar("width",1.);
    double height = ini.get_scalar("height",1.);

    ini.move_to_section("line");
    map<string,double> coords = ini.get_map("coords",empty_string_double);
    vector<int> properties = ini.get_vector("properties",empty_int);

    ini.check_for_wrong_sections();

    cout << "position: " << position << endl;
    cout << "width: " << width << endl;
    cout << "height: " << height << endl;
    cout << "coords: " << coords.size() << " " << coords.find("y1")->second << endl;
    cout << "properties: " << properties.size() << " " << properties[0] << endl;
}
