#ifndef __DATE_H__
#define __DATE_H__

#include <chrono>  //Constructor base inicializará los parámetros al día de hoy
#include <iostream>

#include "configure.hpp"

class Date {
 private:
  int year;
  int month;
  int day;

 public:
  // Constructores

  Date();
  Date(const Date&);
  Date(const int&, const int&, const int&);

  // Interfaces
  // Getter's
  int getYear() const;
  int getMonth() const;
  int getDay() const;

  std::string toString() const;

  // Setter's
  void setYear(const int&);
  void setMonth(const int&);
  void setDay(const int&);

  Date& operator=(const Date&);
};

#endif  // __DATE_H__