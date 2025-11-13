#ifndef __BASEMENU_H__
#define __BASEMENU_H__

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>

#include "configure.hpp"
#include "ownexceptions.hpp"

class BaseMenu {
 protected:
  virtual int readInteger(std::string, const int&, const int&);
  virtual int readPositiveInteger(const std::string&, const bool& = false);
  virtual float readFloat(const std::string&, const float&, const float&);
  virtual float readPositiveFloat(const std::string&, const bool& = false);
  virtual std::string readLinePrompt(const std::string&, bool = false);
  virtual char readChar(const std::string&, const std::string&);
  virtual std::string standarString(std::string);
  virtual std::string clearColor(const std::string&);

  virtual void cleanScreen();
  virtual void errorMessage(const std::string&,
                            const int& = Configure::predeterminatedSizeWindows);

  // Métodos Auxiliares
  virtual void enterToContinue(const bool& = true);
  virtual std::string windowHeader(
      const std::string&,
      const int& = Configure::predeterminatedSizeWindows,
      const std::string& = "═") const;
  virtual std::string divider(
      const std::string& = "═",
      const int& = Configure::predeterminatedSizeWindows) const;
  virtual std::string insertColorText(std::string, std::string);
  virtual std::string centerText(
      std::string,
      const int& = Configure::predeterminatedSizeWindows);

 public:
  virtual void mainMenu() = 0;
  virtual ~BaseMenu();
};

#endif  // __BASEMENU_H__