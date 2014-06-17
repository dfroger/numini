#include "numini.hxx"

NumIni::NumIni(std::string filename):
    m_filename(filename),
    m_section("")
{
    m_root = YAML::LoadFile(m_filename);
}

void
NumIni::move_to_section(std::string section)
{
    m_section = section;
    m_allowed_sections.insert(section);
}

void
NumIni::check_for_wrong_sections()
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
            msg << "Wrong section:" << section << std::endl;
            NUMINI_ERROR(msg.str().c_str());
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
