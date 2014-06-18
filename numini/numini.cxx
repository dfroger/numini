#include "numini.hxx"

#include <fstream>

NumIni::NumIni():
    m_filename(""),
    m_section("")
{
}

NumIni::NumIni(std::string filename):
    m_filename(filename),
    m_section("")
{
    load_file(filename);
}

void
NumIni::load_file(std::string filename)
{
    m_filename = filename;

    // Check file.
    std::ifstream f(filename.c_str());
    bool is_good = f.good();
    f.close();
    if (!is_good) {
        std::ostringstream msg;
        msg << "Can not open file <" << m_filename << "> "
            <<  "for reading." << std::endl;
        NUMINI_ERROR(msg.str().c_str());
    }

    m_root = YAML::LoadFile(m_filename);
}

void
NumIni::move_to_section(std::string section)
{
    m_section = section;
    m_allowed_sections.insert(section);

    m_allowed_keys_per_section[m_section] = std::set<std::string>();
}

void
NumIni::check_for_unknown_sections()
{
    std::string section;
    bool is_in;
    for (YAML::const_iterator it =  m_root.begin() ;
                              it != m_root.end() ; ++it) {
        section = it->first.as<std::string>();
        is_in = m_allowed_sections.find(section)
                != m_allowed_sections.end();
        if (! is_in) {
            std::ostringstream msg;
            msg << "In file <" << m_filename << ">, "
                <<  "unknown section: <" << section << ">."
                << std::endl;
            NUMINI_ERROR(msg.str().c_str());
        }
    }
}

void
NumIni::check_for_unknown_vars()
{
    std::string section, key;
    YAML::Node node;
    bool is_in;
    std::set<std::string> allowed_keys;

    // Iterate on sections.
    for (YAML::const_iterator section_it  = m_root.begin() ; 
                              section_it != m_root.end() ;
                              section_it++ ) {
        section = section_it->first.as<std::string>();
        node = section_it->second;
        allowed_keys = m_allowed_keys_per_section[section];

        // Iteration on keys of current section.
        for (YAML::const_iterator var_it  = node.begin() ; 
                                  var_it != node.end() ;
                                  var_it++ ) {
            key = var_it->first.as<std::string>();
            is_in = allowed_keys.find(key) != allowed_keys.end();
            if (! is_in) {
                std::ostringstream msg;
                msg << "In file <" << m_filename << ">, "
                    << "section: <" << section << ">, "
                    << "unknown key: <" << key << ">."
                    << std::endl;
                NUMINI_ERROR(msg.str().c_str());
            }
        }
    }
}

NumIniError::NumIniError():
    str_(NULL)
{
}

NumIniError::NumIniError(const char * str,const char * file,int line):
    str_(NULL)
{
  std::ostringstream msg;
  msg << file << ":" << line << ": " << str ;
  msg.flush();

  str_ = new char[ strlen( msg.str().c_str() )+1 ];
  strcpy(str_, msg.str().c_str() );
}
const char* NumIniError::what() const throw()
{
  return str_;
}

void numini_error(const char * str,const char * file,int line)
{
  NumIniError err(str,file,line);
  throw err;
}

void numini_error(std::string str,const char * file,int line)
{
  NumIniError err(str.c_str(),file,line);
  throw err;
}
