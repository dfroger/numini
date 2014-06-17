#ifndef NUMINI_HXX_INCLUDED
#define NUMINI_HXX_INCLUDED

#include <string.h>
#include <exception>
#include <string>
#include <map>
#include <vector>

#include "yaml-cpp/yaml.h"

#define NUMINI_ERROR(msg)  numini_error(msg,__FILE__,__LINE__);

class NumIni {
    public:
        
    NumIni(std::string filename);

    void move_to_section(std::string section);

    void check_for_wrong_sections();

    template <class T>
    T
    get_scalar(std::string key, T default_value);

    template <class TKEY, class TVAL>
    std::map<TKEY,TVAL>
    get_map(std::string key, std::map<TKEY,TVAL> default_value);

    template <class T>
    std::vector<T>
    get_vector(std::string key, std::vector<T> default_value);

    private:
        YAML::Node m_root;
        std::string m_filename;
        std::string m_section;
        std::set<std::string> m_allowed_sections;
};

class NumIniError: public std::exception
{  
    public:
        NumIniError();
        NumIniError(const char * str,const char * file,int line);
        virtual ~NumIniError() throw() {}
        virtual const char* what() const throw();
    private:
        char *str_;
};

void numini_error(const char* str, const char* file, int line);
void numini_error(std::string str, const char* file, int line);

#include "numini.txx"

#endif
