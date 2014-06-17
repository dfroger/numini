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

    m_allowed_keys_per_section.find(m_section)->second.insert(key);
}


//////////////////////////////////////////////////////////////////////////////
// Vectors
//////////////////////////////////////////////////////////////////////////////


template <class T>
void
NumIni::get_vector(std::vector<T> &value, std::string key,
                   std::vector<T> default_value)
{
    value = m_root[m_section][key].as< std::vector<T> > (default_value);
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
}


//////////////////////////////////////////////////////////////////////////////
// Maps
//////////////////////////////////////////////////////////////////////////////


template <class TKEY, class TVAL>
void
NumIni::get_map(std::map<TKEY,TVAL> &value, std::string key,
                std::map<TKEY,TVAL> default_value)
{
    value = m_root[m_section][key].as< std::map<TKEY,TVAL> >(default_value);
    m_allowed_keys_per_section.find(m_section)->second.insert(key);
}

#endif
