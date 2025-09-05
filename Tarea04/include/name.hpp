#ifndef __NAME_H__
#define __NAME_H__

#include <string>
#include <iostream>
#include <fstream>

#include "exceptions.hpp"

class Name {
 private:
  std::string first;
  std::string last;

 public:
  Name();
  Name(const Name&);
  Name(const std::string&, const std::string&);

  // Interfaz
  // Setter's
  void setFirst(const std::string&);
  void setLast(const std::string&);

  // Getter's
  std::string getFirst() const;
  std::string getLast() const;

  std::string toString() const;

  Name& operator=(const Name&);

  bool operator==(const Name&) const;
  bool operator != (const Name&) const;
  bool operator < (const Name&) const;
  bool operator > (const Name&) const;
  bool operator <= (const Name&) const;
  bool operator >= (const Name&) const;


  friend std::ostream& operator<<(std::ostream&, const Name&);
  friend std::istream& operator >> (std::istream&, Name&);
};
#endif  // __NAME_H__