#include "numini/node.hxx"

namespace numini
{

Node::Node(std::string filename, std::string section,
           std::string key, YAML::Node node,
           const char* current_node):
    m_filename(filename),
    m_section(section),
    m_key(key),
    m_node(node),
    m_current_node(current_node)
{
}


}
