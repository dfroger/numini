#include <iostream>

#include "param.hxx"

using namespace std;

int main()
{
    Parameters p;
    p.read_config_file("config/normal.yaml");
    cout << p.width() << endl;
}
