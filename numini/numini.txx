#ifndef NUMINI_TXX_INCLUDED
#define NUMINI_TXX_INCLUDED

#include "numini.hxx"

template <class T>
T
NumIni::get_scalar(std::string key, T default_value)
{
    T value = m_root[m_section][key].as<T>(default_value);
    return value;
}

template <class TKEY, class TVAL>
std::map<TKEY,TVAL>
NumIni::get_map(std::string key, std::map<TKEY,TVAL> default_value)
{
    std::map<TKEY,TVAL> value =
        m_root[m_section][key].as< std::map<TKEY,TVAL> >();
    return value;
}

template <class T>
std::vector<T>
NumIni::get_vector(std::string key, std::vector<T> default_value)
{
    std::vector<T> value = m_root[m_section][key].as< std::vector<T> >();
    return value;
}

#endif
