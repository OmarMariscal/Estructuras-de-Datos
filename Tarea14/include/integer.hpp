#ifndef __INTEGER_H__
#define __INTEGER_H__

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

class Integer {
 private:
  int64_t value = 0;

 public:
  Integer();
  Integer(const Integer&);
  Integer(const int64_t&);
  Integer(const std::string&);

  int64_t getValue() const;

  std::string toString() const;
  static std::string toString(const Integer&);

  void setValue(const int64_t&);

  Integer& operator=(const int64_t&);
  Integer& operator=(const Integer&);
  Integer& operator=(const std::string&);

  // Operador
  bool operator==(const Integer&) const;
  bool operator!=(const Integer&) const;
  bool operator<(const Integer&) const;
  bool operator>(const Integer&) const;
  bool operator<=(const Integer&) const;
  bool operator>=(const Integer&) const;

  static int compare(const Integer&, const Integer&);
  int compareTo(const Integer&);

  Integer operator+(const Integer&) const;
  Integer operator-(const Integer&) const;
  Integer operator*(const Integer&) const;
  Integer operator/(const Integer&) const;
  Integer operator%(const Integer&) const;

  Integer operator+(const int64_t&) const;
  Integer operator-(const int64_t&) const;
  Integer operator*(const int64_t&) const;
  Integer operator/(const int64_t&) const;
  Integer operator%(const int64_t&) const;

  Integer& operator++();
  Integer operator++(int);

  Integer& operator--();
  Integer operator--(int);

  Integer& operator+=(const Integer&);
  Integer& operator-=(const Integer&);
  Integer& operator*=(const Integer&);
  Integer& operator/=(const Integer&);
  Integer& operator%=(const Integer&);

  friend std::ostream& operator<<(std::ostream&, const Integer&);
  friend std::istream& operator>>(std::istream&, Integer&);

  // Operadores globales
  // Para poder hacer tanto Integer + int como int + Integer
  friend Integer operator+(const int64_t&, const Integer&);
  friend Integer operator-(const int64_t&, const Integer&);
  friend Integer operator*(const int64_t&, const Integer&);
  friend Integer operator/(const int64_t&, const Integer&);
  friend Integer operator%(const int64_t&, const Integer&);

  friend bool operator==(const int64_t&, const Integer&);
  friend bool operator!=(const int64_t&, const Integer&);
  friend bool operator<(const int64_t&, const Integer&);
  friend bool operator>(const int64_t&, const Integer&);
  friend bool operator<=(const int64_t&, const Integer&);
  friend bool operator>=(const int64_t&, const Integer&);
};

#endif  // __INTEGER_H__