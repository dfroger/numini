#ifndef NUMINI_READER_HXX_INCLUDED
#define NUMINI_READER_HXX_INCLUDED

#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <typeinfo>

#include "yaml-cpp/yaml.h"

#include "numini/node.hxx"

namespace numini
{

class Reader
{
    public:
        Reader();

        Reader(std::string filename);

        void
        load_file(std::string filename);

        void
        move_to_section(std::string section);

        void
        check_for_unknown_sections();

        void
        check_for_unknown_vars();

        Node
        operator() (std::string key);

        /*
        // Scalars
        template <class T>
        T
        readopt_scalar(std::string key, T default_value = T());

        template <class T>
        T
        require_scalar(std::string key);

        // Vectors
        template <class T>
        std::vector<T>
        readopt_vector(std::string key,
                       std::vector<T> default_value = std::vector<T>());

        template <class T>
        std::vector<T>
        require_vector(std::string key);

        // Maps
        template <class TKEY, class TVAL>
        std::map<TKEY,TVAL>
        readopt_map(std::string key,
                    std::map<TKEY,TVAL> default_value);
    //              std::map<TKEY,TVAL> default_value = std::map<TKEY,TVAL>());

        template <class TKEY, class TVAL>
        std::map<TKEY,TVAL>
        require_map(std::string key);

        template <class T>
        T
        convert(YAML::Node node, std::string description);
        */

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


#include "numini/reader.txx"

}

#endif
