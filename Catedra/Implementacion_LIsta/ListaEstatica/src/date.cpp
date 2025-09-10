#include "date.hpp"

using namespace std;

Date::Date() {} //Inicializar al día de hoy

Date::Date(const Date& other) : year(other.year) , month(other.month) , day(other.day){}

Date::Date(const int& y, const int& m, const int& d) : year(y) , month(m), day(d){
    //Hacer Validaciones!!!
}

int Date::getYear() const {
    return year;
}

int Date::getMonth() const{
    return month;
}

int Date::getDay() const{
    return day;
}

string Date::toString() const{
    return to_string(this->day) + "/" + to_string(this->month) + "/" + to_string(this->year);
}

void Date::setYear(const int&y){
    this->year = y; //Hacer Validaciones
}

void Date::setMonth(const int&m){
    this->month = m; //Hacer Validaciones
}

void Date::setDay(const int&d){
    this->day = d; //Hacer Validaciones
}
