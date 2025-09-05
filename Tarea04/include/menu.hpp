#ifndef __MENU_H__
#define __MENU_H__

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "list.hpp"
#include "song.hpp"

class Menu {
 private:
  List<Song> &songList;

  int readInteger(std::string, const int&, const int&);
  Name readName(std::string);
  std::string readLinePrompt(const std::string&, bool = false);

  bool handleOption(const std::string&);
  std::string windowHeader(const int&, const std::string&);

  void mainMenu();
  void insertSong();
  void deleteSong(const int&);
  void deleteAllSongs();
  void editSong(const int&);
  void exitProgram();

  void saveToDisk();
  void readFromDisk();

 public:
  Menu();
  Menu(const Menu&);
  Menu(List<Song>&);
};

#endif  // __MENU_H__