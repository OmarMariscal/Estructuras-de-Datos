#include "name.hpp"

Name::Name() : first("default"), last("default") {}

Name::Name(const Name& other) : first(other.first), last(other.last) {}

Name::Name(const std::string& f, const std::string& l) : first(f), last(l) {}

void Name::setFirst(const std::string& first) {
  if (first.empty())
    throw Exception("Nombre no puede estar vacío, setFirst(Name)");
  this->first = first;
}

void Name::setLast(const std::string& last) {
  if (last.empty())
    throw Exception("Apellido no puede estar vacío, setLast(Name)");
  this->last = last;
}

std::string Name::getFirst() const {
  return this->first;
}

std::string Name::getLast() const {
  return this->last;
}

std::string Name::toString() const {
  return this->first + " " + this->last;
}

Name& Name::operator=(const Name& other) {
  this->first = other.first;
  this->last = other.last;

  return *this;
}

bool Name::operator==(const Name& other) const{
  return this->toString() == other.toString();
}

bool Name::operator != (const Name& other) const{
  return !(*this == other);
}

bool Name::operator < (const Name& other) const{
  return this->toString() < other.toString();
}

bool Name::operator > (const Name& other) const{
  return this->toString() > other.toString();
}

bool Name::operator<=(const Name& other) const {
  return (*this < other) || (*this == other);
}

bool Name::operator>=(const Name& other) const {
  return (*this > other) || (*this == other);
}

std::ostream& operator<<(std::ostream& os, const Name& name){
  os << name.first <<","
      << name.last;

  return os;
}

std::istream& operator >> (std::istream& is, Name& name){
  std::string dataString;
  getline(is, dataString, ',');
  name.first = dataString;
  getline(is, dataString, ',');
  name.last = dataString;

  return is;
}