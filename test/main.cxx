#include <iostream>

#include "param.hxx"

using namespace std;

int main(int argc, char** argv)
{
    string filename = (argc > 1) ? argv[1] : "config/normal.yaml";
        
    Parameters p;
    try {
        p.read_config_file(filename);
    } catch (numini::Error& e) {
        cerr << e.what() << endl;
        return 1;
    }
}
