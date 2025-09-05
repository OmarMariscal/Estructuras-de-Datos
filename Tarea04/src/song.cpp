#include "song.hpp"

using namespace std;

Song::Song() : ranking(-1), songName("default"), author(), interpreter() {}

Song::Song(const Song& other)
    : ranking(other.ranking),
      songName(other.songName),
      author(other.author),
      interpreter(other.interpreter) {}

Song::Song(const int& r, const std::string& n, const Name& a, const Name& i)
    : ranking(r), songName(n), author(a), interpreter(i) {}

void Song::setRanking(const int& ranking) {
  if (ranking <= 0)
    throw Exception("El ranking debe ser positivo");
  this->ranking = ranking;
}

void Song::setSongName(const std::string& songName) {
  if (songName.empty())
    throw Exception("El nombre no puede estar vacio.");
  this->songName = songName;
}

void Song::setAuthor(const Name& author) {
  this->author = author;  // Name tiene sus propias validaciones
}

void Song::setInterpreter(const Name& interpreter) {
  this->interpreter = interpreter;
}

int Song::getRanking() const {
  return this->ranking;
}

std::string Song::getSongName() const {
  return this->songName;
}

Name Song::getAuthor() const {
  return this->author;
}

Name Song::getInterpreter() const {
  return this->interpreter;
}

std::string Song::toString() const {
  ostringstream oss;
  int widthBorder = 60;

  oss << setfill('=') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  oss << "| " << setw((widthBorder / 2) + 10) << "INFORMACION DE LA CANCION"
      << setw((widthBorder / 2) - 12) << "|" << endl;

  oss << setfill('-') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  oss << "Posicion en el Ranking: " << ranking << endl;
  oss << "Nombre de la Cancion: " << songName << endl;
  oss << "Nombre del Autor: " << author.toString() << endl;
  oss << "Nombre del Inteprete: " << interpreter.toString() << endl;

  oss << endl << setfill('=') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  return oss.str();
}

Song& Song::operator=(const Song& other) {
  this->ranking = other.ranking;
  this->songName = other.songName;
  this->author = other.author;
  this->interpreter = other.interpreter;

  return *this;
}

bool Song::operator==(const Song& other) const{
  return this->ranking == other.ranking;
}

bool Song::operator != (const Song& other) const{
  return !(*this == other);
}

bool Song::operator < (const Song& other) const{
  return this->ranking < other.ranking;
}

bool Song::operator > (const Song& other) const {
  return this->ranking > other.ranking;
}

bool Song::operator <= (const Song& other) const {
  return !(*this > other);
}

bool Song::operator >= (const Song& other) const{
  return !(*this < other);
}

std::ostream& operator << (std::ostream& os, const Song& song){
  os << song.ranking << ","
      << song.songName << ","
      << song.author << ","
      << song.interpreter;
  
  return os;

}

std::istream& operator >>(std::istream& is, Song& song){
  string dataString;
  getline(is, dataString, ',');
  song.ranking = stoi(dataString);
  getline(is, song.songName, ',');
  is >> song.author;
  is >> song.interpreter;

  return is;
}


