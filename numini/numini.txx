#ifndef NUMINI_TXX_INCLUDED
#define NUMINI_TXX_INCLUDED

#include "numini.hxx"


//////////////////////////////////////////////////////////////////////////////
// Scalars
//////////////////////////////////////////////////////////////////////////////


template <class T>
void
NumIni::readopt_scalar(T &value, std::string key, T default_value)
{
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if ( node.IsDefined() ) {
        m_read_defined_scalar(value,key);
    } else {
        value = default_value;
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
}

template <class T>
void
NumIni::require_scalar(T &value, std::string key)
{
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
}

template <class T>
void
NumIni::m_read_defined_scalar(T &value, std::string key)
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
void
NumIni::readopt_vector(std::vector<T> &value, std::string key,
                   std::vector<T> default_value)
{
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
void
NumIni::require_vector(std::vector<T> &value, std::string key)
{
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
}

template <class T>
void
NumIni::m_read_defined_vector(std::vector<T> &value, std::string key)
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
void
NumIni::readopt_map(std::map<TKEY,TVAL> &value, std::string key,
                std::map<TKEY,TVAL> default_value)
{
    m_key = key;
    YAML::Node node = m_root[m_section][key];
    if ( node.IsDefined() ) {
        m_read_defined_map(value,key);
    } else {
        value = default_value;
    }
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
}


template <class TKEY, class TVAL>
void
NumIni::require_map(std::map<TKEY,TVAL> &value, std::string key)
{
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
}

template <class TKEY, class TVAL>
void
NumIni::m_read_defined_map(std::map<TKEY,TVAL> &value, std::string key)
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
void
NumIni::convert(T &value, YAML::Node node, std::string description)
{
    try {
        value = node.as<T>();
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

#endif
