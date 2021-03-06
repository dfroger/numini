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
    T value;
    try {
        value = m_node.as<T>();
    } catch (YAML::BadConversion &e) {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read <" << m_key << ">";
        if (m_current_node)
            msg << " (while processing: " << m_current_node << ")";
        msg << ".";
        NUMINI_ERROR(msg.str().c_str());
    }
    return value;
}

}

#endif
