#include "student.hpp"

using namespace std;

Student::Student() { }

Student::Student(const Student& other) : code(other.code), name(other.name), birthDate(other.birthDate), career(other.career), starDate(other.starDate), grade(other.grade){

}

string Student::getCode() const{
    return this->code;
}

Name Student::getName() const{
    return this->name;
}

Date Student::getBirthDate() const{
    return this->birthDate;
}

string Student::getCareer() const{
    return this->career;
}

Date Student::getStartDate() const{
    return this->starDate;
}

float Student::getGrade() const{
    return this->grade;
}

string Student::toString() const{
    string result;
    char myGrade[9];

    sprintf(myGrade, "%6.2f", this->grade);

    result = this->code;
    result += "|";
    result += this->name.toString();
    result.resize(45, ' ');
    result += "|";
    result += this->birthDate.toString();
    result += "|";
    result += this->career;
    result += "|";
    result += this->starDate.toString();
    result += "|";
    result += myGrade;
    result += "|";

    return result;
}

void Student::setCode(const std::string&c){
    this->code = c;
}

void Student::setName(const Name&n){
    this->name = n;
}

void Student::setBirthDate(const Date&b){
    this->birthDate = b;
}

void Student::setCareer(const std::string& c){
    this->career = c;
}

void Student::setStartDate(const Date& s){
    this->starDate = s;
}

void Student::setGrade(const float&g){
    this->grade = g;
}

Student& Student::operator = (const Student& other){
    this->code = other.code;
    this->name = other.name;
    this->birthDate = other.birthDate;
    this->career = other.career;
    this->starDate = other.starDate;
    this->grade = other.grade;

    return *this;
}

ostream& operator << (ostream& os, const Student& s){
    os << s.code << endl;
    os << s.name << endl;
    os << s.birthDate << endl;
    os << s.career << endl;
    os << s.starDate << endl;
    os << s.grade;

    return os;
}

istream& operator >> (istream& is, Student& s){
    string myStr;
    getline(is, s.code);
    is >> s.name;
    is >> s.birthDate;
    getline(is, s.career);
    is >> s.starDate;
    getline(is, myStr);
    s.grade = stof(myStr);

    return is;
}




