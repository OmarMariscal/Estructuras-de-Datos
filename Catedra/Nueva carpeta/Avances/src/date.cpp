#include "date.hpp"

using namespace std;

Date::Date() {} //Inicializar al día de hoy

Date::Date(const Date& other) : year(other.year) , month(other.month) , day(other.day){}

Date::Date(const int& y, const int& m, const int& d) : year(y) , month(m), day(d){
    //Hacer Validaciones!!!
}

int Date::toInt() const{
    return this->year * 10000 + this->month * 100 + this->day;
}

bool Date::isValid() const{
    
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

bool Date::operator == (const Date& other) const{
    return this->toInt() == other.toInt();
}

bool Date::operator != (const Date& other) const{
    return !(*this == other);
}

bool Date::operator < (const Date& other) const{
    return this->toInt() < other.toInt();
}

bool Date::operator > (const Date& other) const{
    return !(*this <= other);
}

bool Date::operator <= (const Date& other) const{
    return *this < other || *this == other;
}

bool Date::operator >=(const Date& other) const{
    return !(*this < other);
}

int Date::compareTo(const Date& other) const{
    return this->toInt() - other.toInt();
}

int Date::compare(const Date& a, const Date& b){
    return a.toInt() - b.toInt();
}

