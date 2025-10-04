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

  void sortDataMerge(const int&, const int&);
  void sortDataMerge(const int&, const int&, int(const T&, const T&));

  void sortDataQuick(const int&, const int&);
  void sortDataQuick(const int&, const int&, int(const T&, const T&));

 public:
  List<T, ARRAYSIZE>();
  List<T, ARRAYSIZE>(const List<T, ARRAYSIZE>&);

  bool isEmpty() const;
  bool isFull() const;
  bool isSorted() const;

  void insertElement(const T&, const int&);
  void deleteData(const int&);
  T* retrieve(const int&);

  // Getter's
  int getFirstPosition() const;
  int getLastPosition() const;

  int getPrevPosition(const int&) const;
  int getNextPosition(const int&) const;

  std::string toString() const;
  std::string toString(const T&, int(const T&, const T&));

  void deleteAll();

  bool isValidPosition(const int&) const;

  int findDataL(const T&);
  int findDataB(const T&);

  void insertSortedData(const T&);

  void sortDataBubble();
  void sortDataInsert();
  void sortDataSelect();
  void sortDataShell();
  void sortDataMerge();
  void sortDataQuick();

  List<T, ARRAYSIZE>& operator=(const List<T, ARRAYSIZE>&);

  template <class X>
  friend std::ostream& operator<<(std::ostream&, const List<X>&);
  template <class X>
  friend std::istream& operator>>(std::istream&, List<X>&);

  // Métodos Extras al Modelo
  bool isSorted(int(const T&, const T&)) const;

  int findDataL(const T&, int(const T&, const T&));
  int findDataB(const T&, int(const T&, const T&));

  void sortDataBubble(int(const T&, const T&));
  void sortDataInsert(int(const T&, const T&));
  void sortDataSelect(int(const T&, const T&));
  void sortDataShell(int(const T&, const T&));
  void sortDataMerge(int(const T&, const T&));
  void sortDataQuick(int(const T&, const T&));

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
bool List<T, ARRAYSIZE>::isEmpty() const {
  return this->last == -1;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() const {
  return this->last == (ARRAYSIZE - 1);
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isSorted() const {
  for (int i = 0; i < this->last; i++)
    if (this->data[i] > this->data[i + 1])
      return false;

  return true;
}

template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isSorted(int cmp(const T&, const T&)) const {
  for (int i = 0; i < this->last; i++)
    if (cmp(this->data[i], this->data[i + 1]) > 0)
      return true;

  return true;
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
  std::ostringstream oss;
  for (int i = 0; i <= this->last; i++)
    oss << this->data[i].toString() << std::endl;

  return oss.str();
}

template <class T, int ARRAYSIZE>
std::string List<T, ARRAYSIZE>::toString(const T& searched,
                                         int cmp(const T&, const T&)) {
  std::ostringstream oss;
  for (int i = 0; i <= this->last; i++)
    if (cmp(this->data[i], searched) == 0)
      oss << this->data[i].toString() << std::endl;

  return oss.str();
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteAll() {
  this->last = -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertSortedData(const T& newData) {
  int i(0);

  while ((i <= this->last) && (newData > this->data[i]))
    i++;

  insertElement(newData, i);
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& searchedData) {
  for (int i = 0; i <= this->last; i++)
    if (this->data[i] == searchedData)
      return i;
  return -1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& searchedData) {
  int i(0), j(this->last), middle;

  while (i <= j) {
    middle = (i + j) / 2;
    if (this->data[middle] == searchedData)
      return middle;
    if (searchedData < this->data[middle])
      j = middle - 1;
    else
      i = middle + 1;
  }
  return -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::swapData(T& a, T& b) {
  T aux = a;
  a = b;
  b = aux;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble() {
  int i(this->last), j;
  bool flag;

  do {
    flag = false;
    j = 0;

    while (j < i) {
      if (this->data[j] > this->data[j + 1]) {
        swapData(this->data[j], this->data[j + 1]);
        flag = true;
      }
      j++;
    }

    i--;
  } while (flag);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert() {
  int i(1), j;
  T aux;

  while (i <= this->last) {
    aux = this->data[i];

    j = i;
    while (j > 0 && aux < this->data[j - 1]) {
      this->data[j] = this->data[j - 1];

      j--;
    }

    if (i != j) {
      this->data[j] = aux;
    }

    i++;
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataSelect() {
  int i(0), j, menor;

  while (i <= this->last) {
    menor = i;

    j = i + 1;

    while (j <= this->last) {
      if (this->data[j] < this->data[menor]) {
        menor = j;
      }
      j++;
    }

    if (i != menor) {
      this->swapData(this->data[i], this->data[menor]);
    }
    i++;
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataShell() {
  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};
  int pos(0), dif(series[pos]), i, j;

  while (dif > 0) {
    i = dif;
    while (i <= this->last) {
      j = i;

      while (j >= dif && this->data[j - dif] > this->data[j]) {
        this->swapData(this->data[j - dif], this->data[j]);
        j -= dif;
      }

      i++;
    }

    dif = series[++pos];
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge() {
  this->sortDataMerge(0, this->last);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge(int cmp(const T&, const T&)) {
  this->sortDataMerge(0, this->last, cmp);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge(const int& leftEdge,
                                       const int& rightEdge) {
  // Criterio de Paro
  if (leftEdge >= rightEdge)
    return;

  int m((leftEdge + rightEdge) / 2);

  // Divide y Vencerás
  this->sortDataMerge(leftEdge, m);
  this->sortDataMerge(m + 1, rightEdge);

  // Intercalación
  static T temp[ARRAYSIZE];

  for (int n(leftEdge); n <= rightEdge; n++)
    temp[n] = this->data[n];

  int i(leftEdge), j(m + 1), x(leftEdge);

  while (i <= m && j <= rightEdge) {
    while (i <= m && temp[i] <= temp[j])
      this->data[x++] = temp[i++];

    if (i <= m)
      while (j <= rightEdge && temp[j] <= temp[i])
        this->data[x++] = temp[j++];
  }

  while (i <= m)
    this->data[x++] = temp[i++];
  while (j <= m)
    this->data[x++] = temp[j++];
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataMerge(const int& leftEdge,
                                       const int& rightEdge,
                                       int cmp(const T&, const T&)) {
  // Criterio de Paro
  if (leftEdge >= rightEdge)
    return;

  int m((leftEdge + rightEdge) / 2);

  // Divide y Vencerás
  this->sortDataMerge(leftEdge, m, cmp);
  this->sortDataMerge(m + 1, rightEdge, cmp);

  // Intercalación
  static T temp[ARRAYSIZE];

  for (int n(leftEdge); n <= rightEdge; n++)
    temp[n] = this->data[n];

  int i(leftEdge), j(m + 1), x(leftEdge);

  while (i <= m && j <= rightEdge) {
    while (i <= m && cmp(temp[i], temp[j]) <= 0)
      this->data[x++] = temp[i++];

    if (i <= m)
      while (j <= rightEdge && cmp(temp[j], temp[i]) <= 0)
        this->data[x++] = temp[j++];
  }

  while (i <= m)
    this->data[x++] = temp[i++];
  while (j <= m)
    this->data[x++] = temp[j++];
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick() {
  this->sortDataQuick(0, this->last);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(int cmp(const T&, const T&)) {
  this->sortDataQuick(0, this->last, cmp);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const int& leftEdge,
                                       const int& rightEdge) {
  // Criterio de paro
  if (leftEdge >= rightEdge)
    return;

  if (leftEdge == rightEdge + 1) {
    if (this->data[leftEdge] > this->data[rightEdge])
      this->swapData(this->data[leftEdge], this->data[rightEdge]);
    return;
  }

  // Separación
  int i(leftEdge), j(rightEdge);

  while (i < j) {
    while (i < j && this->data[i] <= this->data[rightEdge])
      i++;

    while (i < j && this->data[j] >= this->data[rightEdge])
      j--;

    if (i != j)
      this->swapData(this->data[i], this->data[j]);
  }

  if (i != rightEdge)
    this->swapData(this->data[i], this->data[rightEdge]);

  // Divide y Vencerás
  this->sortDataQuick(leftEdge, i - 1);
  this->sortDataQuick(i + 1, rightEdge);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataQuick(const int& leftEdge,
                                       const int& rightEdge,
                                       int cmp(const T&, const T&)) {
  // Criterio de paro
  if (leftEdge >= rightEdge)
    return;

  if (cmp(this->data[leftEdge], this->data[rightEdge + 1]) == 0) {
    if (cmp(this->data[leftEdge], this->data[rightEdge]) > 0)
      this->swapData(this->data[leftEdge], this->data[rightEdge]);
    return;
  }

  // Separación
  int i(leftEdge), j(rightEdge);

  while (i < j) {
    while (i < j && cmp(this->data[i], this->data[rightEdge]) <= 0)
      i++;

    while (i < j && cmp(this->data[j], this->data[rightEdge]) >= 0)
      j--;

    if (i != j)
      this->swapData(this->data[i], this->data[j]);
  }

  if (i != rightEdge)
    this->swapData(this->data[i], this->data[rightEdge]);

  // Divide y Vencerás
  this->sortDataQuick(leftEdge, i - 1, cmp);
  this->sortDataQuick(i + 1, rightEdge, cmp);
}

template <class T, int ARRAYSIZE>
List<T, ARRAYSIZE>& List<T, ARRAYSIZE>::operator=(
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

// Extras al Modelo de la Lista:
template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataL(const T& searchedData,
                                  int cmp(const T&, const T&)) {
  for (int i = 0; i <= this->last; i++)
    if (cmp(searchedData, this->data[i]) == 0)
      return i;

  return -1;
}

template <class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findDataB(const T& searchedData,
                                  int cmp(const T&, const T&)) {
  int i(0), j(this->last), middle;

  while (i <= j) {
    middle = (i + j) / 2;

    if (cmp(searchedData, this->data[middle]) == 0)
      return middle;
    if (cmp(searchedData, this->data[middle]) < 0)
      j = middle - 1;
    else
      i = middle + 1;
  }

  return -1;
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertSortedData(const T& newData,
                                          int cmp(const T&, const T&)) {
  int i(0);

  while ((i <= this->last) && (cmp(newData, this->data[i]) > 0))
    i++;

  insertElement(newData, i);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataBubble(int cmp(const T&, const T&)) {
  int i(this->last), j;
  bool flag;

  do {
    flag = false;
    j = 0;

    while (j < i) {
      if (cmp(this->data[j], this->data[j + 1]) > 0) {
        swapData(this->data[j], this->data[j + 1]);
        flag = true;
      }
      j++;
    }

    i--;
  } while (flag);
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataInsert(int cmp(const T&, const T&)) {
  int i(1), j;
  T aux;

  while (i <= this->last) {
    aux = this->data[i];

    j = i;
    while (j > 0 && cmp(aux, this->data[j - 1]) < 0) {
      this->data[j] = this->data[j - 1];

      j--;
    }

    if (i != j) {
      this->data[j] = aux;
    }

    i++;
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataSelect(int cmp(const T&, const T&)) {
  int i(0), j, menor;

  while (i <= this->last) {
    menor = i;

    j = i + 1;

    while (j <= this->last) {
      if (cmp(this->data[j], this->data[menor]) < 0) {
        menor = j;
      }
      j++;
    }

    if (i != menor) {
      this->swapData(this->data[i], this->data[menor]);
    }
    i++;
  }
}

template <class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortDataShell(int cmp(const T&, const T&)) {
  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};
  int pos(0), dif(series[pos]), i, j;

  while (dif > 0) {
    i = dif;
    while (i <= this->last) {
      j = i;

      while (j >= dif && cmp(this->data[j - dif], this->data[j]) > 0) {
        this->swapData(this->data[j - dif], this->data[j]);
        j -= dif;
      }

      i++;
    }

    dif = series[++pos];
  }
}

#endif  // __LIST_H__