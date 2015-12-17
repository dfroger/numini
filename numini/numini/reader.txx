#ifndef NUMINI_READER_TXX_INCLUDED
#define NUMINI_READER_TXX_INCLUDED

#include "numini/reader.hxx"

namespace numini
{

template<typename T>
T
Reader::operator() (std::string key, const T& default_value)
{
    T value;
    YAML::Node node = m_root[m_section][key];
    if (node.IsDefined() ) {
        // TODO: check conversion
        value = node.as<T>();
    } else {
        value = default_value;
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
    return value;
}
}

#endif
