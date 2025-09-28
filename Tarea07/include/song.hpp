#ifndef __SONG_H__
#define __SONG_H__

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "name.hpp"

class Song {
 private:
  int ranking;
  std::string songName;
  Name author;
  Name interpreter;
  std::string mp3Name;

 public:
  Song();
  Song(const Song&);

  /// @brief
  /// @param  Ranking
  /// @param  NombreCancion
  /// @param  NombreAutor
  /// @param  NombreInterprete
  /// @param  NombreMP3
  Song(const int&,
       const std::string&,
       const Name&,
       const Name&,
       const std::string&);

  // Interfaz:
  // Setter's
  void setRanking(const int&);
  void setSongName(const std::string&);
  void setAuthor(const Name&);
  void setInterpreter(const Name&);
  void setMp3Name(const std::string&);

  // Getter's
  int getRanking() const;
  std::string getSongName() const;
  Name getAuthor() const;
  Name getInterpreter() const;
  std::string getMp3Name() const;

  /// @brief Función toString para la lsit.hpp
  /// @param  widthRanking
  /// @param  widthSongName
  /// @param  widthName
  /// @param  widthMP3
  std::string toString(const int& = 10,
                       const int& = 35,
                       const int& = 30,
                       const int& = 25) const;  // Para impresiones en list.hpp

  /// @brief Función de 1 sola canción
  /// @param widthBorder
  /// @return
  std::string toStringOnly(
      const int& = 60) const;  // Para impresiones de solo 1 canción

  Song& operator=(const Song&);

  // Operadores Relacionales que utilizan el ranking como compardor
  bool operator==(const Song&) const;
  bool operator!=(const Song&) const;
  bool operator<(const Song&) const;
  bool operator>(const Song&) const;
  bool operator<=(const Song&) const;
  bool operator>=(const Song&) const;

  int compareTo(const Song&) const;
  static int compare(const Song&, const Song&);

  static int compareBySongName(const Song&, const Song&);
  static int compareByAutor(const Song&, const Song&);
  static int compareByInterpreter(const Song&, const Song&);
  static int compareByMP3Name(const Song&, const Song&);

  friend std::ostream& operator<<(std::ostream&, const Song&);
  friend std::istream& operator>>(std::istream&, Song&);
};
#endif  // __SONG_H__