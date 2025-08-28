#pragma once
//Librerías del enguaje
#include <string>
//Librerías Propias
#include "name.hpp"
#include "date.hpp"

//Si se tienen más de tres parámetros, no hay que incluir Constructor Parametrizados
class Student{
    private:
        std::string code;
        Name name;
        Date birthDate;
        std::string career;
        Date starDate;
        float grade;

    public: 
        Student();
        Student(const Student&);

        std::string getCode() const;
        Name getName() const;
        Date getBirthDate() const;
        std::string getCareer() const;
        Date getStartDate() const;
        float getGrade() const;

        std::string toString() const;

        void setCode(const std::string&);
        void setName(const Name&);
        void setBirthDate(const Date&);
        void setCareer(const std::string&);
        void setStartDate(const Date&);
        void setGrade(const float&);

};