#include <string.h>
#include <sstream>

#include "numini/error.hxx"

namespace numini
{

Error::Error():
    str_(NULL)
{
}

Error::Error(const char * str,const char * file,int line):
    str_(NULL)
{
  std::ostringstream msg;
  msg << file << ":" << line << ": " << str ;
  msg.flush();

  str_ = new char[ strlen( msg.str().c_str() )+1 ];
  strcpy(str_, msg.str().c_str() );
}
const char* Error::what() const throw()
{
  return str_;
}

void error(const char * str,const char * file,int line)
{
  Error err(str,file,line);
  throw err;
}

void error(std::string str,const char * file,int line)
{
  Error err(str.c_str(),file,line);
  throw err;
}

}
