#ifndef __SONG_H__
#define __SONG_H__

#include <iomanip>
#include <sstream>
#include <string>

#include "name.hpp"

class Song {
 private:
  int ranking;
  std::string songName;
  Name author;
  Name interpreter;

 public:
  Song();
  Song(const Song&);

  /// @brief
  /// @param  Ranking
  /// @param  NombreCancion
  /// @param  NombreAutor
  /// @param  NombreInterprete
  Song(const int&, const std::string&, const Name&, const Name&);

  // Interfaz:
  // Setter's
  void setRanking(const int&);
  void setSongName(const std::string&);
  void setAuthor(const Name&);
  void setInterpreter(const Name&);

  // Getter's
  int getRanking() const;
  std::string getSongName() const;
  Name getAuthor() const;
  Name getInterpreter() const;

  std::string toString() const;

  Song& operator=(const Song&);
};
#endif  // __SONG_H__