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

        template<typename T>
        T
        operator() (std::string key, const T& default_value);

        Node
        operator() (YAML::Node node);
        
    private:
        YAML::Node m_root;
        std::string m_filename;
        std::string m_section;
        std::string m_key;
        std::set<std::string> m_allowed_sections;
        std::map<std::string,std::set<std::string> >
            m_allowed_keys_per_section;
};

}

#include "numini/reader.txx"

#endif
