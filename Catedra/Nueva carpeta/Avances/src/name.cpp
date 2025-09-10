#include "name.hpp"

using namespace std;

Name::Name(){

}

Name::Name(const Name& other) : last(other.last), fist(other.fist){}

Name::Name(const string& l, const string& f) : last(l) , fist(f){};

string Name::getLast() const{
    return this->last;
}

string Name::getFirst() const{
    return this->fist;
}

string Name::toString() const{
    return this->last + ", " + this->fist;
}

void Name::setFirst(const string& f){
    this->fist = f;
}

bool Name::operator == (const Name& other) const{
    return this->toString() == other.toString();
}

bool Name::operator != (const Name& other) const {
    return !(*this == other);
}

bool Name::operator < (const Name& other) const {
    return *this < other || *this == other;
}

bool Name::operator >(const Name& other) const{
    return !(*this <= other);
}

bool Name::operator >=(const Name& other) const{
    return !(*this < other);
}

int Name::compareTo(const Name& other) const{
    return this->toString().compare(other.toString());
}

int Name::compare(const Name& a, const Name& b){
    return a.toString().compare(b.toString());
}

void Name::setLast(const string& l){
    this->last = l;
}

Name& Name::operator=(const Name& other){
    this->last = other.last;
    this->fist = other.fist;
    return *this;
}

