#ifndef NUMINI_NODE_HXX_INCLUDED
#define NUMINI_NODE_HXX_INCLUDED

#include <string>

#include "yaml-cpp/yaml.h"

namespace numini
{
    
class Node
{
    public:
        Node(std::string filename, std::string section,
             std::string key, YAML::Node node);

    operator double();

    private:
        std::string m_filename;
        std::string m_section;
        std::string m_key;
        YAML::Node m_node;
};

}

#endif
