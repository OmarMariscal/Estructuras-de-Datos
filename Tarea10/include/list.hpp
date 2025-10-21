#ifndef __LIST_H__
#define __LIST_H__

#include <string>

#include "ownexceptions.hpp"

using namespace std;

// Definición
template <class T>
class List {
  class Node;

 public:
  typedef Node* Position;

 private:
  class Node {
   private:
    T data;
    Position next = nullptr;

   public:
    Node();
    Node(const T&);

    T& getData();
    Position getNext() const;

    void setData(const T&);
    void setNext(const Position&);
  };

  bool isValidPosition(const Position&) const;
  void add(const List<T>&);

  Position anchor = nullptr;

 public:
  List();
  List(const List<T>&);

  ~List();

  bool isEmpty() const;

  void insertData(const T&, const Position&);
  void insertData(const T&, const int&);

  void deleteData(const Position&);
  void deleteData(const int&);

  Position getFirstPos() const;
  Position getLastPos() const;
  int getLastPosition() const;
  Position getPrevPos(const Position&) const;
  Position getNextPos(const Position&) const;

  Position findData(const T&) const;
  int findDataL(const T&) const;
  int findDataL(const T&, int(const T&, const T&)) const;
  int findDataB(const T&, int(const T&, const T&)) const;

  T& retrieve(const Position&);
  T* retrieve(const int&);

  string toString() const;
  void insertSortedData(const T&);

  /*Existen Aquí ordenamientos muy ineficientes que sólo fueron adaptados para
     mantener las funcionaledes del programa que ya tenía como la búsqueda
     binaria o un sortDataShell, que requirieron de implementaciones poco
     eficientes se implementaron SOLO CON LA FINALIDAD DE QUE EL PROGRAMA NO
     PERDIERA DICHAS FUNCIONES pero en casos de implementación real NO DEBEN DE
     IMPLEMENTARSE EN UNA LISTA CON ESTAS CONDICIONES Dicho aquello y
     considerando que se buscó la práctica y dejar el programa con las maayores
     funcionalidades intactas, seguimos
  */
  void sortDataBubble();
  void sortDataInsert();
  void sortDataSelect();
  void sortDataShell();

  void deleteAll();

  List<T>& operator=(const List<T>&);

  void sortDataBubble(int(const T&, const T&));
  void sortDataInsert(int(const T&, const T&));
  void sortDataSelect(int(const T&, const T&));
  void sortDataShell(int(const T&, const T&));
  bool isValidPosition(const int&) const;
  Position getNodeAt(int) const;

  template <class U>
  friend std::ostream& operator<<(std::ostream&, const List<U>&);
  template <class U>
  friend std::istream& operator>>(std::istream&, List<U>&);
};

// Implementación
// Node
template <class T>
List<T>::Node::Node() {}

template <class T>
List<T>::Node::Node(const T& element) : data(element) {}

template <class T>
T& List<T>::Node::getData() {
  return this->data;
}

template <class T>
typename List<T>::Position List<T>::Node::getNext() const {
  return this->next;
}

template <class T>
void List<T>::Node::setData(const T& data) {
  this->data = data;
}

template <class T>
void List<T>::Node::setNext(const typename List<T>::Position& pointer) {
  this->next = pointer;
}

// Lista

template <class T>
bool List<T>::isValidPosition(const Position& pointer) const {
  Position aux = this->anchor;

  while (aux != nullptr) {
    if (aux == pointer) {
      return true;
    }
    aux = aux->getNext();
  }

  return false;
}

template <class T>
bool List<T>::isValidPosition(const int& index) const {
  if (index < 0) {
    return false;
  }

  Position aux = this->anchor;
  int count = 0;

  while (aux != nullptr) {
    if (count == index) {
      return true;
    }
    aux = aux->getNext();
    count++;
  }

  return false;
}

template <class T>
void List<T>::add(const List<T>& other) {
  Position aux(other.anchor), lastInsert(this->getLastPos()), newNode(nullptr);

  while (aux != nullptr) {
    newNode = new Node(aux->getData());
    if (newNode == nullptr)
      throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

    if (lastInsert == nullptr)
      this->anchor = newNode;
    else
      lastInsert->setNext(newNode);

    lastInsert = newNode;
    aux = aux->getNext();
  }
}

template <class T>
List<T>::List() {}

template <class T>
List<T>::List(const List<T>& other) {
  this->add(other);
}

template <class T>
List<T>::~List() {
  this->deleteAll();
}

template <class T>
bool List<T>::isEmpty() const {
  return this->anchor == nullptr;
}

template <class T>
void List<T>::insertData(const T& element,
                         const typename List<T>::Position& position) {
  if (position != nullptr && !this->isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition();

  Position newNode(new Node(element));
  if (newNode == nullptr)
    throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");

  if (position == nullptr) {  // Insertar al Principio
    newNode->setNext(this->anchor);
    this->anchor = newNode;
  }

  else {  // Cualquier otra
    newNode->setNext(position->getNext());
    position->setNext(newNode);
  }
}

template <class T>
void List<T>::deleteData(const typename List<T>::Position& position) {
  if (!this->isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition();

  if (position == this->anchor)  // Eliminar el primero
    this->anchor = position->getNext();

  else  // Cualquier otra Posición
    this->getPrevPos(position)->setNext(position->getNext());

  delete position;
}

template <class T>
typename List<T>::Position List<T>::getFirstPos() const {
  return this->anchor;
}

template <class T>
typename List<T>::Position List<T>::getLastPos() const {
  if (this->isEmpty())
    return nullptr;

  Position aux(this->anchor);
  while (aux->getNext() != nullptr)
    aux = aux->getNext();

  return aux;
}

template <class T>
typename List<T>::Position List<T>::getPrevPos(
    const typename List<T>::Position& position) const {
  if (position == nullptr)
    return nullptr;

  Position aux(this->anchor);
  while (aux != nullptr && aux->getNext() != position)
    aux = aux->getNext();

  return aux;
}
template <class T>
typename List<T>::Position List<T>::getNextPos(
    const typename List<T>::Position& position) const {
  return this->isValidPosition(position) ? position->getNext() : nullptr;
}

template <class T>
typename List<T>::Position List<T>::findData(const T& dataSearched) const {
  Position aux(this->anchor);

  while (aux != nullptr && aux->getData() != dataSearched)
    aux = aux->getNext();
  return aux;
}

template <class T>
T& List<T>::retrieve(const typename List<T>::Position& p) {
  if (!this->isValidPosition(p))
    throw DataContainersExceptions::InvalidPosition();
  return p->getData();
}

template <class T>
string List<T>::toString() const {
  ostringstream oss;
  Position aux(this->anchor);
  int cont;
  while (aux != nullptr) {
    oss << "| " << std::to_string(cont)
        << std::setw(11 - std::to_string(cont).size()) << ""
        << aux->getData().toString() << "\n";
    cont++;
    aux = aux->getNext();
  }

  return oss.str();
}

template <class T>
void List<T>::deleteAll() {
  Position aux;

  while (this->anchor != nullptr) {
    aux = this->anchor;
    this->anchor = aux->getNext();
    delete aux;
  }
}

template <class T>
void List<T>::sortDataBubble() {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr)
    return;

  bool swapped;
  Position ptr1;
  Position lptr = nullptr;

  do {
    swapped = false;
    ptr1 = this->anchor;

    while (ptr1->getNext() != lptr) {
      if (ptr1->getData() > ptr1->getNext()->getData()) {
        T temp = ptr1->getData();
        ptr1->setData(ptr1->getNext()->getData());
        ptr1->getNext()->setData(temp);
        swapped = true;
      }
      ptr1 = ptr1->getNext();
    }
    lptr = ptr1;
  } while (swapped);
}

template <class T>
void List<T>::sortDataInsert() {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr)
    return;

  Position sorted = this->anchor;
  Position current = this->anchor->getNext();
  sorted->setNext(nullptr);

  while (current != nullptr) {
    Position next = current->getNext();

    if (current->getData() < sorted->getData()) {
      current->setNext(sorted);
      sorted = current;
    } else {
      Position temp = sorted;
      while (temp->getNext() != nullptr &&
             temp->getNext()->getData() <= current->getData()) {
        temp = temp->getNext();
      }
      current->setNext(temp->getNext());
      temp->setNext(current);
    }

    current = next;
  }

  this->anchor = sorted;
}

template <class T>
void List<T>::sortDataSelect() {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
    return;
  }

  Position current = this->anchor;
  while (current != nullptr) {
    Position minNode = current;
    Position scanner = current->getNext();

    while (scanner != nullptr) {
      if (scanner->getData() < minNode->getData()) {
        minNode = scanner;
      }
      scanner = scanner->getNext();
    }

    if (minNode != current) {
      T temp = current->getData();
      current->setData(minNode->getData());
      minNode->setData(temp);
    }

    current = current->getNext();
  }
}

template <class T>
void List<T>::sortDataShell() {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
    return;
  }

  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};

  int size = 0;
  Position temp = this->anchor;
  while (temp != nullptr) {
    size++;
    temp = temp->getNext();
  }

  int pos = 0;
  int gap = series[pos];

  while (gap > size) {
    gap = series[++pos];
  }

  while (gap > 0) {
    for (int i = gap; i < size; i++) {
      Position nodeI = this->getNodeAt(i);
      T tempData = nodeI->getData();

      int j = i;
      while (j >= gap) {
        Position nodeJMinusGap = this->getNodeAt(j - gap);

        if (nodeJMinusGap->getData() > tempData) {
          Position nodeJ = this->getNodeAt(j);
          nodeJ->setData(nodeJMinusGap->getData());
          j -= gap;
        } else {
          break;
        }
      }

      Position nodeJ = this->getNodeAt(j);
      nodeJ->setData(tempData);
    }

    gap = series[++pos];
  }
}

template <class T>
List<T>& List<T>::operator=(const List<T>& other) {
  this->deleteAll();
  this->add(other);

  return *this;
}

template <class T>
void List<T>::sortDataBubble(int cmp(const T&, const T&)) {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
    return;
  }

  bool flag;
  Position lptr = nullptr;

  do {
    flag = false;
    Position ptr1 = this->anchor;

    while (ptr1->getNext() != lptr) {
      if (cmp(ptr1->getData(), ptr1->getNext()->getData()) > 0) {
        T temp = ptr1->getData();
        ptr1->setData(ptr1->getNext()->getData());
        ptr1->getNext()->setData(temp);
        flag = true;
      }
      ptr1 = ptr1->getNext();
    }
    lptr = ptr1;
  } while (flag);
}

template <class T>
void List<T>::sortDataInsert(int cmp(const T&, const T&)) {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr)
    return;

  Position sorted = this->anchor;
  Position current = this->anchor->getNext();
  sorted->setNext(nullptr);

  while (current != nullptr) {
    Position next = current->getNext();

    if (cmp(current->getData(), sorted->getData()) < 0) {
      current->setNext(sorted);
      sorted = current;
    } else {
      Position temp = sorted;
      while (temp->getNext() != nullptr &&
             cmp(temp->getNext()->getData(), current->getData()) <= 0) {
        temp = temp->getNext();
      }
      current->setNext(temp->getNext());
      temp->setNext(current);
    }

    current = next;
  }

  this->anchor = sorted;
}

template <class T>
void List<T>::sortDataSelect(int cmp(const T&, const T&)) {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
    return;
  }

  Position current = this->anchor;

  while (current != nullptr) {
    Position minNode = current;
    Position scanner = current->getNext();

    while (scanner != nullptr) {
      if (cmp(scanner->getData(), minNode->getData()) < 0) {
        minNode = scanner;
      }
      scanner = scanner->getNext();
    }

    if (minNode != current) {
      T temp = current->getData();
      current->setData(minNode->getData());
      minNode->setData(temp);
    }

    current = current->getNext();
  }
}

template <class T>
void List<T>::sortDataShell(int cmp(const T&, const T&)) {
  if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
    return;
  }

  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};

  int size = 0;
  Position temp = this->anchor;
  while (temp != nullptr) {
    size++;
    temp = temp->getNext();
  }

  int pos = 0;
  int gap = series[pos];

  while (gap > size) {
    gap = series[++pos];
  }

  while (gap > 0) {
    for (int i = gap; i < size; i++) {
      Position nodeI = this->getNodeAt(i);
      T tempData = nodeI->getData();

      int j = i;
      while (j >= gap) {
        Position nodeJMinusGap = this->getNodeAt(j - gap);

        if (cmp(nodeJMinusGap->getData(), tempData) > 0) {
          Position nodeJ = this->getNodeAt(j);
          nodeJ->setData(nodeJMinusGap->getData());
          j -= gap;
        } else {
          break;
        }
      }

      Position nodeJ = this->getNodeAt(j);
      nodeJ->setData(tempData);
    }

    gap = series[++pos];
  }
}

template <class T>
typename List<T>::Position List<T>::getNodeAt(int index) const {
  Position current = this->anchor;
  int count = 0;

  while (current != nullptr && count < index) {
    current = current->getNext();
    count++;
  }

  return current;
}

template <class T>
int List<T>::getLastPosition() const {
  if (this->isEmpty()) {
    return -1;
  }

  int count = 0;
  Position aux = this->anchor;
  while (aux->getNext() != nullptr) {
    aux = aux->getNext();
    count++;
  }
  return count;
}

// insertData con índice
template <class T>
void List<T>::insertData(const T& element, const int& index) {
  if (index < 0) {
    throw DataContainersExceptions::InvalidPosition();
  }

  if (index == 0) {
    this->insertData(element, nullptr);
    return;
  }

  Position prev = this->getNodeAt(index - 1);
  if (prev == nullptr) {
    throw DataContainersExceptions::InvalidPosition();
  }

  this->insertData(element, prev);
}

// deleteData con índice
template <class T>
void List<T>::deleteData(const int& index) {
  Position target = this->getNodeAt(index);
  if (target == nullptr) {
    throw DataContainersExceptions::InvalidPosition();
  }
  this->deleteData(target);
}

// retrieve con índice
template <class T>
T* List<T>::retrieve(const int& index) {
  Position target = this->getNodeAt(index);
  if (target == nullptr) {
    throw DataContainersExceptions::InvalidPosition();
  }
  return &(target->getData());
}

// findDataL - Búsqueda lineal simple
template <class T>
int List<T>::findDataL(const T& dataSearched) const {
  Position aux = this->anchor;
  int index = 0;

  while (aux != nullptr) {
    if (aux->getData() == dataSearched) {
      return index;
    }
    aux = aux->getNext();
    index++;
  }

  return -1;
}

// findDataL con comparador
template <class T>
int List<T>::findDataL(const T& dataSearched,
                       int cmp(const T&, const T&)) const {
  Position aux = this->anchor;
  int index = 0;

  while (aux != nullptr) {
    if (cmp(aux->getData(), dataSearched) == 0) {
      return index;
    }
    aux = aux->getNext();
    index++;
  }

  return -1;
}

// findDataB - Búsqueda binaria
template <class T>
int List<T>::findDataB(const T& dataSearched,
                       int cmp(const T&, const T&)) const {
  if (this->isEmpty()) {
    return -1;
  }

  int left = 0;
  int right = this->getLastPosition();

  while (left <= right) {
    int mid = left + (right - left) / 2;
    Position midNode = this->getNodeAt(mid);

    int comparison = cmp(midNode->getData(), dataSearched);

    if (comparison == 0) {
      return mid;
    } else if (comparison < 0) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1;
}

// insertSortedData - Inserción en orden
template <class T>
void List<T>::insertSortedData(const T& element) {
  Position newNode = new Node(element);
  if (newNode == nullptr) {
    throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");
  }

  if (this->anchor == nullptr || element < this->anchor->getData()) {
    newNode->setNext(this->anchor);
    this->anchor = newNode;
    return;
  }

  Position current = this->anchor;
  while (current->getNext() != nullptr &&
         current->getNext()->getData() < element) {
    current = current->getNext();
  }

  newNode->setNext(current->getNext());
  current->setNext(newNode);
}

template <class U>
std::ostream& operator<<(std::ostream& os, const List<U>& list) {
  typename List<U>::Position aux = list.anchor;
  int index = 0;

  while (aux != nullptr) {
    os << aux->getData();
    aux = aux->getNext();
    index++;
  }

  return os;
}

template <class U>
std::istream& operator>>(std::istream& is, List<U>& list) {
  U element;
  try {
    while (is >> element) {
      list.insertSortedData(element);
    }
  } catch (const std::invalid_argument& ex) {
  }

  return is;
}

#endif  // __LIST_H__