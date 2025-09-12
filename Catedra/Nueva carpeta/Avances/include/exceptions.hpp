#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>
#include <stdexcept>

namespace DateExceptions{
    class InvalidDate : public std::runtime_error{
        public:
            explicit InvalidDate(const std::string& msg) : runtime_error(msg){}
    };
}

namespace NameExceptions{
    
}


#endif // __EXCEPTIONS_H__