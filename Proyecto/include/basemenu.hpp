#ifndef __BASEMENU_H__
#define __BASEMENU_H__

#include <string>
#include "name.hpp"
#include "category.hpp"

class BaseMenu{
    private:
        virtual int readInteger(std::string, const int&, const int&);
        virtual float readFloat(const std::string&, const float&, const float&);
        virtual Name readName(std::string, const std::string& = "Ingrese el Nombre: ", const std::string& = "Ingrese el Apellido");
        virtual std::string readLinePrompt(const std::string&, bool = false);
        virtual char readChar(const std::string&, const std::string&);
        virtual Category readCategory(const std::string&);
        virtual std::string standarString(std::string);
        virtual std::string clearColor(const std::string&); 
        
    public:
        virtual void mainMenu() = 0;
};


#endif // __BASEMENU_H__