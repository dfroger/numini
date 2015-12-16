#include <iostream>

#include "param.hxx"

using namespace std;

int main()
{
    //string filename = "config/normal.yaml";
    string filename = "config/wrong_element_type_in_sequence.yaml";
    Parameters p;
    p.read_config_file(filename);
    cout << p.position() << endl;
}
