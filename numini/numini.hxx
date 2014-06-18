#ifndef NUMINI_HXX_INCLUDED
#define NUMINI_HXX_INCLUDED

#include <string.h>
#include <sstream>
#include <exception>
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

#include "yaml-cpp/yaml.h"

#define NUMINI_ERROR(msg)  numini_error(msg,__FILE__,__LINE__);

class NumIni {
    public:
        
    NumIni();
    NumIni(std::string filename);

    void
    load_file(std::string filename);

    void move_to_section(std::string section);

    void check_for_unknown_sections();

    void check_for_unknown_vars();

    // Scalars
    template <class T>
    void
    readopt_scalar(T &value, std::string key, T default_value = T());

    template <class T>
    void
    require_scalar(T &value, std::string key);

    // Vectors
    template <class T>
    void 
    readopt_vector(std::vector<T> &value, std::string key,
                   std::vector<T> default_value = std::vector<T>());

    template <class T>
    void 
    require_vector(std::vector<T> &value, std::string key);

    // Maps
    template <class TKEY, class TVAL>
    void
    readopt_map(std::map<TKEY,TVAL> &value, std::string key,
                std::map<TKEY,TVAL> default_value = std::map<TKEY,TVAL>());

    template <class TKEY, class TVAL>
    void
    require_map(std::map<TKEY,TVAL> &value, std::string key);

    template <class T>
    void
    convert(T &value, YAML::Node node, std::string description);


    private:
        YAML::Node m_root;
        std::string m_filename;
        std::string m_section;
        std::string m_key;
        std::set<std::string> m_allowed_sections;
        std::map<std::string,std::set<std::string> >
            m_allowed_keys_per_section;

        template <class T>
        void
        m_read_defined_scalar(T &value, std::string key);

        template <class T>
        void
        m_read_defined_vector(std::vector<T> &value, std::string key);

        template <class TKEY, class TVAL>
        void
        m_read_defined_map(std::map<TKEY,TVAL> &value, std::string key);
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
