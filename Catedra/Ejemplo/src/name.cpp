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

std::istream& operator >> (std::istream& is, Name& n){
    getline(is, n.last);
    getline(is, n.fist);

    return is;
}

std::ostream& operator << (std::ostream&, const Name&)
{
    
}

std::istream& operator >> (istream& os, Name& n){
    
}

std::ostream& operator << (ostream& os, const Name& n){
    os << n.last << endl;
    os << n.fist;

    return os;
}

void Name::setLast(const string& l){
    this->last = l;
}

Name& Name::operator=(const Name& other){
    this->last = other.last;
    this->fist = other.fist;
    return *this;
}

