#ifndef NUMINI_NODE_TXX_INCLUDED
#define NUMINI_NODE_TXX_INCLUDED

#include <typeinfo>

#include "numini/node.hxx"
#include "numini/error.hxx"

namespace numini
{

template <typename T>
Node::operator T()
{
    try {
        return m_node.as<T>();
    } catch (YAML::TypedBadConversion<T> &e) {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read <" << m_key << ">: "
            << "expected a type: " << typeid(T).name() << ", "
            << "but got value: <" << m_node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
}

}

#endif
