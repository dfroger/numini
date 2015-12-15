#include <typeinfo>

#include "numini/node.hxx"
#include "numini/error.hxx"

namespace numini
{

Node::Node(std::string filename, std::string section,
           std::string key, YAML::Node node):
    m_filename(filename),
    m_section(section),
    m_key(key),
    m_node(node)
{
}

Node::operator double()
{
    try {
        double value = m_node.as<double>();
    } catch (YAML::TypedBadConversion<double> &e) {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read <" << m_key << ">: "
            << "expected a type: " << typeid(double).name() << ", "
            << "but got value: <" << m_node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
}

}
