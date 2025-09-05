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
    char myDate[12];

    sprintf(myDate, "%02i/%02i/&04i", this->day, this->month, this->year);

    return myDate;
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

ostream& operator << (ostream& os, const Date& d){
    os << d.year << endl;
    os << d.month << endl;
    os << d.day << endl;

    return os;
}

istream& operator >> (istream& is, Date& d){
    string myStr;

    getline(is, myStr);
    d.year = stoi(myStr);
    getline(is, myStr);
    d.month = stoi(myStr);
    getline(is, myStr);
    d.day = stoi(myStr);

    return is;
}


