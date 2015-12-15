#ifndef NUMINI_READER_TXX_INCLUDED
#define NUMINI_READER_TXX_INCLUDED

#include "numini/reader.hxx"

namespace numini
{

//////////////////////////////////////////////////////////////////////////////
// Scalars
//////////////////////////////////////////////////////////////////////////////


/*
template <class T>
T
Reader::readopt_scalar(std::string key, T default_value)
{
    T value;
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if ( node.IsDefined() ) {
        m_read_defined_scalar(value,key);
    } else {
        value = default_value;
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
    return value;
}

template <class T>
T
Reader::require_scalar(std::string key)
{
    T value;
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if (node.IsDefined() ) {
        m_read_defined_scalar(value,key);
    } else {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "variable <" << key << "> "
            << "is required."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
    return value;
}

template <class T>
void
Reader::m_read_defined_scalar(T &value, std::string key)
{
    YAML::Node node = m_root[m_section][key];
    try {
        value = node.as<T>();
    } catch (YAML::TypedBadConversion<T> &e) {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read <" << key << ">: "
            << "expected a type: " << typeid(T).name() << ", "
            << "but got value: <" << node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
}


//////////////////////////////////////////////////////////////////////////////
// Vectors
//////////////////////////////////////////////////////////////////////////////


template <class T>
std::vector<T>
Reader::readopt_vector(std::string key, std::vector<T> default_value)
{
    std::vector<T> value,
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if ( node.IsDefined() ) {
        m_read_defined_vector(value,key);
    } else {
        value = default_value;
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
}

template <class T>
std::vector<T>
Reader::require_vector(std::string key)
{
    std::vector<T> value;
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if (node.IsDefined() ) {
        m_read_defined_vector(value,key);
    } else {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "variable <" << key << "> "
            << "is required."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
    return value;
}

template <class T>
void
Reader::m_read_defined_vector(std::vector<T> &value, std::string key)
{
    YAML::Node node = m_root[m_section][key];
    std::ostringstream msg;
    if (!node.IsSequence()) {
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read <" << key << ">: "
            << "expected a type: vector<" << typeid(T).name() << ">, "
            << "but got non sequence value: <" << node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
    try {
        value = node.as< std::vector<T> > ();
    } catch (YAML::TypedBadConversion<T> &e) {
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read on element of <" << key << ">: "
            << "expected a type: vector<" << typeid(T).name() << ">, "
            << "but got value: <" << node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
}


//////////////////////////////////////////////////////////////////////////////
// Maps
//////////////////////////////////////////////////////////////////////////////


template <class TKEY, class TVAL>
std::map<TKEY,TVAL>
Reader::readopt_map(std::string key,
                    std::map<TKEY,TVAL> default_value)
{
    std::map<TKEY,TVAL> value;
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if ( node.IsDefined() ) {
        m_read_defined_map(value,key);
    } else {
        value = default_value;
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
    return value;
}


template <class TKEY, class TVAL>
std::map<TKEY,TVAL>
Reader::require_map(std::string key)
{
    std::map<TKEY,TVAL> value;
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if (node.IsDefined() ) {
        m_read_defined_map(value,key);
    } else {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "variable <" << key << "> "
            << "is required."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
    return value;
}

template <class TKEY, class TVAL>
void
Reader::m_read_defined_map(std::map<TKEY,TVAL> &value, std::string key)
{
    YAML::Node node = m_root[m_section][key];
    std::ostringstream msg;
    if (!node.IsMap()) {
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read <" << key << ">: "
            << "expected a type: map<" 
            << typeid(TKEY).name() << ","
            << typeid(TVAL).name() << ">, "
            << "but got non map value: <" << node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
    try {
        value = node.as< std::map<TKEY,TVAL> > ();
    } catch (YAML::TypedBadConversion<TVAL> &e) {
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "failed to read on element of <" << key << ">: "
            << "expected a type: map<" << typeid(TVAL).name() << ">, "
            << "but got value: <" << node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
}


//////////////////////////////////////////////////////////////////////////////
// Objects
//////////////////////////////////////////////////////////////////////////////


template <class T>
T
Reader::convert(YAML::Node node, std::string description)
{
    try {
        return node.as<T>();
    } catch (YAML::TypedBadConversion<T> &e) {
        std::ostringstream msg;
        msg << "In file <" << m_filename << ">, "
            << "section <" << m_section << ">, "
            << "variable <" << m_key << ">: "
            << "faied to read " << description << ": " 
            << "expected type: <" << typeid(T).name() << ">, "
            << "but got value: <" << node << ">."
            << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }
}
*/

}

#endif
