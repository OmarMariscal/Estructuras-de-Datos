#ifndef __LIST_H__
#define __LIST_H__

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "ownexceptions.hpp"

template <class T, int ARRAYSIZE = 1024>
class List {
 private:
  T data[ARRAYSIZE];
  int last;

  void copyAll(const List<T, ARRAYSIZE>&);

  void swapData(T&, T&);

 public:
  List<T, ARRAYSIZE>();
  List<T, ARRAYSIZE>(const List<T, ARRAYSIZE>&);

  bool isEmpty();
  bool isFull();
  void insertElement(const T&, const int&);
  void deleteData(const int&);
  T* retrieve(const int&);

  // Getter's
  int getFirstPosition() const;
  int getLastPosition() const;

  int getPrevPosition(const int&) const;
  int getNextPosition(const int&) const;

  std::string toString() const;

  void deleteAll();

  bool isValidPosition(const int&) const;

  int findDataL (const T&);
  int findDataB (const T&);

  void insertSortedData(const T&);

  void sortDataBubble();
  void sortDataInsert();

  List<T, ARRAYSIZE> operator=(const List<T, ARRAYSIZE>&);

  template <class X>
  friend std::ostream& operator<<(std::ostream&, const List<X>&);
  template <class X>
  friend std::istream& operator>>(std::istream&, List<X>&);

  //Métodos Extras al Modelo
  int findDataL(const T&, int(const T&, const T&));
  int findDataB(const T&, int(const T&, const T&));

  void sortDataBubble(int(const T&, const T&));
  void sortDataInsert(int(const T&, const T&));
  

  void insertSortedData(const T&, int(const T&, const T&));
};

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List() : last(-1) {}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::copyAll(const List<T, ARRAYSIZE>& other) {
  for (int i = 0; i < other.last; i++)
    this->data[i] = other.data[i];
  this->last = other.last;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPosition(const int& position) const {
  return !(position > last || position < 0);
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(const List<T, ARRAYSIZE>& other) {
  copyAll(other);
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() {
  return this->last == -1;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() {
  return this->last == (ARRAYSIZE - 1);
}

// Inserción en el Punto de Interés
template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertElement(const T& newData, const int& position) {
  if (isFull())
    throw DataContainersExceptions::MemoryDeficiency(
        "Lista Llena, InsertElement(List)");

  if (!isValidPosition(position) && position != last + 1)
    throw DataContainersExceptions::InvalidPosition(
        "Posicion Invalida, InsertElement(List)");

  for (int i = last; i >= position; i--)
    this->data[i + 1] = this->data[i];
  this->data[position] = newData;
  last++;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteData(const int& position) {
  if (!isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition(
        "Poscion Invalida, delteData(List)");

  for (int i = position; i < last; i++)
    this->data[i] = this->data[i + 1];
  last--;
}

template <class T, int ARRAYSIZE>
T* List<T, ARRAYSIZE>::retrieve(const int& position) {
  if (!isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition(
        "Posicion Invalida, retrieve(List)");
  return &data[position];
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPosition() const {
  return isEmpty() ? -1 : 0;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPosition() const {
  return this->last;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getPrevPosition(const int& position) const {
  return (!isValidPosition(position) || position == 0) ? -1 : (position - 1);
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getNextPosition(const int& position) const {
  return (!isValidPosition(position) || position == last) ? -1 : (position + 1);
}

template <class T, int ARRAYSIZE>
std::string List<T, ARRAYSIZE>::toString() const {
  if (this->last < 0 )
    return "";

  std::string result;
  for(int i = 0; i <= this->last; i++)
    result += std::to_string(this->data[i]);

  return result;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteAll() {
  this->last = -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertSortedData(const T& newData){
  int i(0);

  while( (i <= this->last) && (newData > this->data[i]) )
    i++;

  insertElement(newData, i);
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& searchedData){
  for(int i = 0; i <= this->last; i++)
    if(this->data[i] == searchedData)
      return i;
  return -1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& searchedData){
  int i(0), j(this->last), middle;

  while(i <= j){
    middle = (i + j) / 2;
    if(this->data[middle] == searchedData)
      return middle;
    if(searchedData < this->data[middle])
      j = middle - 1;
    else
      i = middle + 1;      
  }
  return -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::swapData(T& a, T& b){
  T aux = a;
  a = b;
  b = aux;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble(){
  int i(this->last), j;
  bool flag;

  do{
    flag = false;
    j = 0;

    while(j < i){
      if(this->data[j] > this->data[j+1]){
        swapData(this->data[j], this->data[j+1]);
        flag = true;
      }
      j++;
    }

    i--;
  } while(flag);

}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert(){
  int i(1), j;
  T aux;

  while(i < = this->last){
    aux = this->data[i];

    j = i;
    while(j > 0 && aux < this->data[j - 1]){
      this->data[j] = this->data[j - 1];

      j--;
    }

    if(i != j){
      this->data[j] = aux;
    }

    i++;
  }
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE> List<T, ARRAYSIZE>::operator=(
    const List<T, ARRAYSIZE>& other) {
  copyAll(other);

  return *this;
}

template <class X>
std::ostream& operator<<(std::ostream& os, const List<X>& list) {
  int i = 0;
  while (i <= list.last)
    os << list.data[i++] << "," << std::endl;

  return os;
}

template <class X>
std::istream& operator>>(std::istream& is, List<X>& list) {
  X obj;
  std::string aux;

  try {
    while (is >> obj) {
      if (!list.isFull())
        list.data[++list.last] = obj;
    }
  } catch (const std::invalid_argument& ex) {
  }
  return is;
}

//Extras al Modelo de la Lista:
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& searchedData, int cmp(const T&, const T&)){
  for(int i = 0; i <= this->last; i++)
    if( cmp(searchedData, this->data[i]) == 0 )
      return i;

    return -1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& searchedData, int cmp(const T&, const T&)){
  int i(0), j(this->last), middle;

  while(i <= j){
    middle = (i + j) / 2;

    if(cmp(searchedData, this->data[middle]) == 0)
      return middle;
    if(cmp(searchedData, this->data[middle]) < 0)
      j = middle - 1;
    else
      i = middle + 1;
  }

  return -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertSortedData(const T& newData, int cmp(const T&, const T&)){
  int i(0);

  while( (i <= this->last) && (cmp(newData, this->data[i]) > 0) )
    i++;

  insertElement(newData, i);
}


template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble(int cmp(const T&, const T&)){
  int i(this->last), j;
  bool flag;

  do{
    flag = false;
    j = 0;

    while(j < i){
      if(cmp(this->data[j], this->data[j+1]) > 0){
        swapData(this->data[j], this->data[j+1]);
        flag = true;
      }
      j++;
    }

    i--;
  } while(flag);

}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert(int cmp(const T&, const T&)){
  int i(1), j;
  T aux;

  while(i < = this->last){
    aux = this->data[i];

    j = i;
    while(j > 0 && cmp(aux, this->data[j - 1] < 0)){
      this->data[j] = this->data[j - 1];

      j--;
    }

    if(i != j){
      this->data[j] = aux;
    }

    i++;
  }
}


#endif  // __LIST_H__