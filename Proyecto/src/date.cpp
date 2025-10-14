#include "date.hpp"

using namespace std;

Date::Date() {
    auto now = chrono::system_clock::now();
    time_t t= std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&t);

    this->day = local_tm.tm_mday;
    this->month = local_tm.tm_mon + 1;
    this->year = local_tm.tm_year + 1900;
} //Inicializar al día de hoy

Date::Date(const Date& other) : year(other.year) , month(other.month) , day(other.day){}

Date::Date(const int& y, const int& m, const int& d) : year(y) , month(m), day(d){
    //Hacer Validaciones!!!
}

int Date::toInt() const{
    return this->year * 10000 + this->month * 100 + this->day;
}

bool Date::isValid(const int& year, const int& month, const int& day) const{
    int monthDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(year == 0 || month < 1 || month > 12)
        return false;
    
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0) )
        monthDay[2]++;

    if(day < 1 || day > monthDay[month])
        return false;
    
    return true;
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
    this->year = y;  //Hacer Validaciones
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

Date& Date::operator = (const Date& other){
    this->year = other.year;
    this->month = other.month;
    this->day = other.day;

    return *this;
}

nlohmann::json Date::toJson() const{
    nlohmann::json js{
        {"year", this->year},
        {"month", this->month},
        {"day", this->day},
    };

    return js;
}

void Date::fromJson(const nlohmann::json& js){
    this->year = js.at("year").get<int>();
    this->month = js.at("month").get<int>();
    this->day = js.at("day").get<int>();
}


std::ostream& operator << (std::ostream& os, const Date& date){
    //PENDIENTE: REALIZAR EN FORMATO .JSON    
}

std::istream& operator >> (std::istream& is, Date& date){
    //PENDIENTE: REALIZAR EN FORMATO .JSON
}

