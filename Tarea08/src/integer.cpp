#include <integer.hpp>

Integer::Integer() : value(0) {}

Integer::Integer(const Integer& other) : value(other.value) {}

Integer::Integer(const int64_t& v) : value(v) {}

Integer::Integer(const std::string& value) : value(std::stoi(value)) {}

int64_t Integer::getValue() const {
  return value;
}

std::string Integer::toString() const {
  return std::to_string(value);
}

std::string Integer::toString(const Integer& integer) {
  return integer.toString();
}

void Integer::setValue(const int64_t& v) {
  this->value = v;
}

Integer& Integer::operator=(const Integer& other) {
  if (this != &other)
    this->value = other.value;
  return *this;
}

Integer& Integer::operator=(const std::string& value) {
  this->value = std::stoi(value);
  return *this;
}

Integer& Integer::operator=(const int64_t& value) {
  this->value = value;
  return *this;
}

bool Integer::operator==(const Integer& other) const {
  return this->value == other.value;
}

bool Integer::operator!=(const Integer& other) const {
  return this->value != other.value;
}

bool Integer::operator<(const Integer& other) const {
  return this->value < other.value;
}

bool Integer::operator>(const Integer& other) const {
  return this->value > other.value;
}

bool Integer::operator<=(const Integer& other) const {
  return this->value <= other.value;
}

bool Integer::operator>=(const Integer& other) const {
  return this->value >= other.value;
}

int Integer::compare(const Integer& integerA, const Integer& integerB) {
  return integerA.value - integerB.value;
}

int Integer::compareTo(const Integer& other) {
  return this->value - other.value;
}

Integer Integer::operator+(const Integer& other) const {
  return Integer(this->value + other.value);
}

Integer Integer::operator-(const Integer& other) const {
  return Integer(this->value - other.value);
}

Integer Integer::operator*(const Integer& other) const {
  return Integer(this->value * other.value);
}

Integer Integer::operator/(const Integer& other) const {
  return Integer(this->value / other.value);
}

Integer Integer::operator%(const Integer& other) const {
  return Integer(this->value % other.value);
}

Integer Integer::operator+(const int64_t& value) const {
  return Integer(this->value + value);
}

Integer Integer::operator-(const int64_t& value) const {
  return Integer(this->value - value);
}

Integer Integer::operator*(const int64_t& value) const {
  return Integer(this->value * value);
}

Integer Integer::operator/(const int64_t& value) const {
  return Integer(this->value / value);
}

Integer Integer::operator%(const int64_t& value) const {
  return Integer(this->value % value);
}

Integer& Integer::operator++() {
  this->value++;
  return *this;
}

Integer Integer::operator++(int) {
  Integer temp(*this);
  ++value;
  return temp;
}

Integer& Integer::operator--() {
  this->value--;
  return *this;
}

Integer Integer::operator--(int) {
  Integer temp(*this);
  --value;
  return temp;
}

Integer& Integer::operator+=(const Integer& other) {
  this->value += other.value;
  return *this;
}

Integer& Integer::operator-=(const Integer& other) {
  this->value -= other.value;
  return *this;
}

Integer& Integer::operator*=(const Integer& other) {
  this->value *= other.value;
  return *this;
}

Integer& Integer::operator/=(const Integer& other) {
  this->value /= other.value;
  return *this;
}

Integer& Integer::operator%=(const Integer& other) {
  this->value %= other.value;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Integer& integer) {
  os << integer.getValue();
  return os;
}

std::istream& operator>>(std::istream& is, Integer& integer) {
  int64_t temp;
  is >> temp;
  if (is) {
    integer.setValue(temp);
  }
  return is;
}

Integer operator+(const int64_t& value, const Integer& integer) {
  return Integer(value + integer.value);
}

Integer operator-(const int64_t& value, const Integer& integer) {
  return Integer(value - integer.value);
}

Integer operator*(const int64_t& value, const Integer& integer) {
  return Integer(value * integer.value);
}

Integer operator/(const int64_t& value, const Integer& integer) {
  return Integer(value / integer.value);
}

Integer operator%(const int64_t& value, const Integer& integer) {
  return Integer(value % integer.value);
}

bool operator==(const int64_t& value, const Integer& integer) {
  return value == integer.value;
}

bool operator!=(const int64_t& value, const Integer& integer) {
  return value != integer.value;
}

bool operator<(const int64_t& value, const Integer& integer) {
  return value < integer.value;
}

bool operator>(const int64_t& value, const Integer& integer) {
  return value > integer.value;
}

bool operator<=(const int64_t& value, const Integer& integer) {
  return value <= integer.value;
}

bool operator>=(const int64_t& value, const Integer& integer) {
  return value >= integer.value;
}
