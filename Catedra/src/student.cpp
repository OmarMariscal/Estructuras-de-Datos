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

    result = this->code;
    result += "|";
    result += this->name.toString();
    result += "|";
    result += this->birthDate.toString();
    result += "|";
    result += this->career;
    result += "|";
    result += this->starDate.toString();
    result += "|";
    result += to_string(this->grade);
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


