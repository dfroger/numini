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
    YAML::Node node = m_root[m_section][key];
    if ( node.IsDefined() ) {
        m_read_defined_scalar(value,key);
    } {
        value = default_value;
    }
}

template <class T>
void
NumIni::require_scalar(T &value, std::string key)
{
    T default_value;

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
            << "expected a type: <" << typeid(T).name() << ">, "
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
NumIni::get_vector(std::string key, std::vector<T> default_value)
{
    std::vector<T> value = m_root[m_section][key].as< std::vector<T> >();
    return value;
}


//////////////////////////////////////////////////////////////////////////////
// Maps
//////////////////////////////////////////////////////////////////////////////


template <class TKEY, class TVAL>
std::map<TKEY,TVAL>
NumIni::get_map(std::string key, std::map<TKEY,TVAL> default_value)
{
    std::map<TKEY,TVAL> value =
        m_root[m_section][key].as< std::map<TKEY,TVAL> >();
    return value;
}

#endif
