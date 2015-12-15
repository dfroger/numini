#ifndef NUMINI_ERROR_HXX_INCLUDED
#define NUMINI_ERROR_HXX_INCLUDED

#include <exception>
#include <string>

#define NUMINI_ERROR(msg)  error(msg,__FILE__,__LINE__);

namespace numini
{

class Error: public std::exception
{  
    public:
        Error();
        Error(const char * str,const char * file,int line);
        virtual ~Error() throw() {}
        virtual const char* what() const throw();
    private:
        char *str_;
};

void error(const char* str, const char* file, int line);
void error(std::string str, const char* file, int line);

}

#endif
