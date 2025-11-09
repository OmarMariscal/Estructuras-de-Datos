#ifndef __DoubleLinkedList_H__
#define __DoubleLinkedList_H__

#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

#include "../lib/nlohmann/json.hpp"
#include "ownexceptions.hpp"

using namespace std;

// Definición
template <class T>
class DoubleLinkedList {
  class Node;

 public:
  typedef Node* Position;

 private:
  int totalElements = 0;
  class Node {
   private:
    T* dataPtr = nullptr;
    Position prev = nullptr;
    Position next = nullptr;

   public:
    Node();
    Node(const T&);

    ~Node();

    T* getDataPtr();
    T& getData();

    Position getPrev() const;
    Position getNext() const;

    void setDataPtr(T*);
    void setData(const T&);
    void setNext(const Position&);
    void setPrev(const Position&);
  };

  bool isValidPosition(const Position&) const;
  void add(const DoubleLinkedList<T>&);
  void swapData(Position, Position);

  //Helpers para el ordenamiento recursivo
  Position partition(Position, Position);
  void quicksortRecursive(Position, Position);

  Position partition(Position, Position, int(const T&, const T&));
  void quicksortRecursive(Position, Position, int(const T&, const T&));

  Position header = nullptr;

 public:
  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList<T>&);

  ~DoubleLinkedList();

  bool isEmpty() const;
  bool isSorted() const;

  void insertData(const Position&, const T&);
  void insertSortedData(const T&);
  void deleteData(const Position&);
  int getTotalElements() const;
  Position getFirstPos() const;
  Position getLastPos() const;
  Position getPrevPos(const Position&) const;
  Position getNextPos(const Position&) const;
  Position getNodeAt(int index) const;

  Position findData(const T&) const;
  int findIndex(const T&) const;
  T& retrieve(const Position&);

  string toString(const bool& = false) const;
  string toString(const T&, int(const T&, const T&)) const;

  nlohmann::json toJson() const;
  void fromJson(const nlohmann::json&);

  //Ordenamientos Iterativos
  void sortDataBubble();
  void sortDataInsert();
  void sortDataSelect();
  void sortDataShell();

  //Ordenamiento Recursivo
  void sortDataQuick();

  void deleteAll();

  DoubleLinkedList<T>& operator=(const DoubleLinkedList<T>&);

  bool isSorted(int(const T&, const T&)) const;

  void insertSortedData(const T&, int(const T&, const T&));
  Position findData(const T&, int(const T&, const T&)) const;
  int findIndex(const T&, int(const T&, const T&)) const;

  void sortDataBubble(int(const T&, const T&));
  void sortDataInsert(int(const T&, const T&));
  void sortDataSelect(int(const T&, const T&));
  void sortDataShell(int(const T&, const T&));
  void sortDataQuick(int(const T&, const T&));

  template <class X>
  friend std::ostream& operator<<(std::ostream&, const DoubleLinkedList<X>&);
  template <class X>
  friend std::istream& operator>>(std::istream&, DoubleLinkedList<X>&);
};

// Implementación
// Node
template <class T>
DoubleLinkedList<T>::Node::Node() {}

template <class T>
DoubleLinkedList<T>::Node::Node(const T& element) : dataPtr(new T(element)) {
  if (dataPtr == nullptr) {
    throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible, Node");
  }
}

template <class T>
DoubleLinkedList<T>::Node::~Node() {
  delete this->dataPtr;
}

template <class T>
T* DoubleLinkedList<T>::Node::getDataPtr() {
  return this->dataPtr;
}

template <class T>
T& DoubleLinkedList<T>::Node::getData() {
  if (this->dataPtr == nullptr)
    throw NodeExceptions::MemoryNotAvaliable("Dato Inexistente, getData");
  return *this->dataPtr;
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::Node::getPrev() const {
  return this->prev;
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::Node::getNext() const {
  return this->next;
}

template <class T>
void DoubleLinkedList<T>::Node::setDataPtr(T* p) {
  this->dataPtr = p;
}

template <class T>
void DoubleLinkedList<T>::Node::setData(const T& e) {
  if (this->dataPtr == nullptr) {
    this->dataPtr = new T(e);
    if (this->dataPtr == nullptr)
      throw NodeExceptions::MemoryNotAvaliable("Memoria no disponible, setData");
  } else
    *this->dataPtr = e;
}

template <class T>
void DoubleLinkedList<T>::Node::setPrev(const typename DoubleLinkedList<T>::Position& pointer) {
  this->prev = pointer;
}

template <class T>
void DoubleLinkedList<T>::Node::setNext(const typename DoubleLinkedList<T>::Position& pointer) {
  this->next = pointer;
}

// DoubleLinkedLista

template <class T>
bool DoubleLinkedList<T>::isValidPosition(const Position& pointer) const {
  Position aux(this->header->getNext());

  while (aux != header) {
    if (aux == pointer) {
      return true;
    }
    aux = aux->getNext();
  }

  return false;
}

template <class T>
void DoubleLinkedList<T>::add(const DoubleLinkedList<T>& other) {
  Position aux(other.header->getNext()), newNode;

  while (aux != other.header) {
    if (newNode = new Node(aux->getData()) == newNode == nullptr)
      throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

    newNode->setPrev(this->header->getPrev());
    newNode->setNext(this->header);

    this->header->getPrev()->setNext(newNode);
    this->header->setPrev(newNode);
    this->totalElements++;

    aux = aux->getNext();
  }
}

template <class T>
void DoubleLinkedList<T>::swapData(Position a, Position b) {
  T temp = a->getData();
  a->setData(b->getData());
  b->setData(temp);
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList() : header(new Node), totalElements(0) {
  if (this->header == nullptr)
    throw NodeExceptions::MemoryNotAvaliable("Memoria no Disponible, DoubleLinkedList");

  this->header->setPrev(this->header);
  this->header->setNext(this->header);
}

template <class T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other) : totalElements(other.totalElements) {
  this->add(other);
}

template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  this->deleteAll();

  delete this->header;
}

template <class T>
bool DoubleLinkedList<T>::isEmpty() const {
  return this->header->getNext() == this->header;
}

template <class T>
bool DoubleLinkedList<T>::isSorted() const{
    //Lista vacía o con un solo elemento está, por definición, ordenada
    if(this->totalElements == 0 || this->totalElements == 1)
        return true;

    Position aux(this->header->getNext());
    while(aux->getNext() != this->header){
        if(aux->getData() > aux->getNext()->getData())
            return false;
        aux = aux->getNext();
    }
    return true;
}

template <class T>
void DoubleLinkedList<T>::insertData(const typename DoubleLinkedList<T>::Position& position,
                         const T& element) {
  if (position != nullptr && !this->isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition();

  Position newNode(new Node(element));
  if (newNode == nullptr)
    throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");

  Position insPos(position == nullptr ? header : position);

  newNode->setPrev(insPos);
  newNode->setNext(insPos->getNext());

  insPos->getNext()->setPrev(newNode);
  insPos->setNext(newNode);
  this->totalElements++;
}

template <class T>
void DoubleLinkedList<T>::insertSortedData(const T& element) {
  Position newNode(new Node(element));
  if (newNode == nullptr)
    throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");

  Position aux(this->header->getNext());

  while (aux != this->header && aux->getData() < newNode->getData())
    aux = aux->getNext();

  newNode->setPrev(aux);
  newNode->setNext(aux->getNext());

  aux->getNext()->setPrev(newNode);
  aux->setNext(newNode);
  this->totalElements++;
}

template <class T>
void DoubleLinkedList<T>::deleteData(const typename DoubleLinkedList<T>::Position& position) {
  if (!this->isValidPosition(position))
    throw DataContainersExceptions::InvalidPosition();

  position->getPrev()->setNext(position->getNext());
  position->getNext()->setPrev(position->getPrev());

  delete position;
  this->totalElements--;
}

template <class T>
int DoubleLinkedList<T>::getTotalElements() const {
  return this->totalElements;
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::getFirstPos() const {
  return this->isEmpty() ? nullptr : this->header->getNext();
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::getLastPos() const {
  return this->isEmpty() ? nullptr : this->header->getPrev();
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::getPrevPos(
    const typename DoubleLinkedList<T>::Position& position) const {
  return position == this->header->getNext() || !this->isValidPosition(position)
             ? nullptr
             : position->getPrev();
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::getNextPos(
    const typename DoubleLinkedList<T>::Position& position) const {
  return position == this->header->getPrev() || !this->isValidPosition(position)
             ? nullptr
             : position->getNext();
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::findData(const T& dataSearched) const {
  Position aux(this->header->getNext());

  while (aux != this->header) {
    if (aux->getData() == dataSearched)
      return aux;
    aux = aux->getNext();
  }

  return nullptr;
}

template <class T>
int DoubleLinkedList<T>::findIndex(const T& dataSearched) const {
  Position aux(this->header->getNext());
    int i(0);
  while (aux != this->header) {
    if (aux->getData() == dataSearched)
      return i;
    aux = aux->getNext();
    i++;
  }

  return -1;
}

template <class T>
T& DoubleLinkedList<T>::retrieve(const typename DoubleLinkedList<T>::Position& p) {
  if (!this->isValidPosition(p))
    throw DataContainersExceptions::InvalidPosition();
  return p->getData();
}

template <class T>
string DoubleLinkedList<T>::toString(const bool& numered) const {
    ostringstream oss;
    Position aux(this->header->getNext());
    int i(1);

    while(aux != this->header){
        if(numered)
            oss << i << ". ";
        oss << aux->getData().toString() << endl;
        aux = aux->getNext();
    }

  return oss.str();
}

template <class T>
string DoubleLinkedList<T>::toString(const T& searched, int cmp(const T&, const T&)) const {
  int cont(0);
  ostringstream oss;
  Position aux(this->header->getNext());

  while (aux != this->header) {
    if (cmp(searched, aux->getData()) == 0) 
      oss << aux->getData().toString() << endl;
    cont++;
    aux = aux->getNext();
  }
  return oss.str();
}

template <class T>
nlohmann::json DoubleLinkedList<T>::toJson() const{
    nlohmann::json js;
    Position aux(this->header->getNext());
    js["data"] = nlohmann::json::array();
    
    while(aux != this->header){
        js["data"].push_back(aux->getData().toJson());
        aux = aux->getNext();
    }
    return js;
}

template <class T>
void DoubleLinkedList<T>::fromJson(const nlohmann::json& js){
    if(js.empty())
        return;
    try{
        this->deleteAll();    
        T obj;
        for(const auto& data : js){
            obj.fromJson(data);
            this->insertData(this->getLastPos(), obj);
        }        
    } catch (const nlohmann::json::exception& ex){
        throw JsonExceptions::InvalidJsonFile();
    }
}

template <class T>
void DoubleLinkedList<T>::deleteAll() {
  Position aux;

  while (this->header->getNext() != this->header) {
    aux = this->header->getNext();

    this->header->setNext(aux->getNext());
    delete aux;
  }

  this->header->setPrev(this->header);
  this->totalElements = 0;
}

template <class T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList<T>& other) {
  this->deleteAll();
  this->add(other);
  this->totalElements = other.totalElements;

  return *this;
}

template <class T>
void DoubleLinkedList<T>::sortDataBubble() {
  bool swapped;
  typename DoubleLinkedList<T>::Position lptr = this->header;
  do {
    swapped = false;
    typename DoubleLinkedList<T>::Position ptr = this->header->getNext();
    while (ptr->getNext() != lptr) {
      typename DoubleLinkedList<T>::Position nxt = ptr->getNext();

      if (ptr->getData() > nxt->getData()) {
        this->swapData(ptr, nxt);
        swapped = true;
      }
      ptr = ptr->getNext();
    }

    lptr = ptr;
  } while (swapped);
}


template <class T>
bool DoubleLinkedList<T>::isSorted(int cmp(const T&, const T&)) const{
    //Lista vacía o con un solo elemento está, por definición, ordenada
    if(this->totalElements == 0 || this->totalElements == 1)
        return true;

    Position aux(this->header->getNext());
    while(aux->getNext() != this->header){
        if(cmp(aux->getData(), aux->getNext()->getData()) > 0)
            return false;
        aux = aux->getNext();
    }
    return true;
}

template <class T>
void DoubleLinkedList<T>::sortDataInsert() {
  if (this->isEmpty())
    return;

  typename DoubleLinkedList<T>::Position current = this->header->getNext()->getNext();

  while (current != this->header) {
    T key = current->getData();
    typename DoubleLinkedList<T>::Position mover = current->getPrev();

    while (mover != this->header && mover->getData() > key) {
      mover->getNext()->setData(mover->getData());
      mover = mover->getPrev();
    }

    mover->getNext()->setData(key);
    current = current->getNext();
  }
}

template <class T>
void DoubleLinkedList<T>::sortDataSelect() {
  if (this->isEmpty())
    return;

  Position current = this->header->getNext();
  while (current != this->header) {
    Position minNode = current;
    Position scanner = current->getNext();

    while (scanner != this->header) {
      if (scanner->getData() < minNode->getData())
        minNode = scanner;

      scanner = scanner->getNext();
    }

    if (minNode != current)
      this->swapData(minNode, current);

    current = current->getNext();
  }
}

template <class T>
void DoubleLinkedList<T>::sortDataShell() {
  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};

  int size = 0;
  Position temp = this->getFirstPos();
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
void DoubleLinkedList<T>::sortDataQuick() {
  if (this->isEmpty()) 
    return;
  this->quicksortRecursive(this->getFirstPos(), this->getLastPos());
}

template <class T>
void DoubleLinkedList<T>::quicksortRecursive(Position low, Position high) {
  if (low == nullptr || high == nullptr || low == this->header ||
      high == this->header || low == high) {
    return;
  }
  Position pivot = this->partition(low, high);

  this->quicksortRecursive(low, pivot->getPrev());
  this->quicksortRecursive(pivot->getNext(), high);
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::partition(Position low, Position high) {
  T pivotValue = high->getData();
  Position i = low->getPrev();

  for (Position j = low; j != high; j = j->getNext()) {
    if (j->getData() < pivotValue) {
      i = (i == this->header) ? this->getFirstPos() : i->getNext();
      this->swapData(i, j);
    }
  }
  i = (i == this->header) ? this->getFirstPos() : i->getNext();
  this->swapData(i, high);

  return i;
}

template <class T>
void DoubleLinkedList<T>::insertSortedData(const T& element, int cmp(const T&, const T&)) {
  Position newNode(new Node(element));
  if (newNode == nullptr)
    throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");

  Position aux(this->header->getNext());

  while (aux != this->header && cmp(aux->getData(), newNode->getData()) < 0)
    aux = aux->getNext();

  newNode->setPrev(aux);
  newNode->setNext(aux->getNext());

  aux->getNext()->setPrev(newNode);
  aux->setNext(newNode);
  this->totalElements++;
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::findData(const T& dataSearched, int cmp(const T&, const T&)) const {
  Position aux(this->header->getNext());

  while (aux != this->header) {
    if (cmp(aux->getData(), dataSearched) == 0)
      return aux;
    aux = aux->getNext();
  }

  return nullptr;
}

template <class T>
int DoubleLinkedList<T>::findIndex(const T& dataSearched, int cmp(const T&, const T&)) const {
  Position aux(this->header->getNext());
    int i(0);
  while (aux != this->header) {
    if (cmp(aux->getData(), dataSearched) == 0)
      return i;
    aux = aux->getNext();
    i++;
  }

  return -1;
}

template <class T>
void DoubleLinkedList<T>::sortDataBubble(int cmp(const T&, const T&)) {
  if (this->isEmpty() || this->header->getNext()->getNext() == this->header)
    return;

  bool swapped;
  typename DoubleLinkedList<T>::Position lptr = this->header;
  do {
    swapped = false;
    typename DoubleLinkedList<T>::Position ptr = this->header->getNext();
    while (ptr->getNext() != lptr) {
      typename DoubleLinkedList<T>::Position nxt = ptr->getNext();
      if (cmp(ptr->getData(), nxt->getData()) > 0) {
        this->swapData(ptr, nxt);
        swapped = true;
      }
      ptr = ptr->getNext();
    }
    lptr = ptr;
  } while (swapped);
}

template <class T>
void DoubleLinkedList<T>::sortDataInsert(int cmp(const T&, const T&)) {
  if (this->isEmpty() || this->header->getNext()->getNext() == this->header)
    return;

  typename DoubleLinkedList<T>::Position current = this->header->getNext()->getNext();

  while (current != this->header) {
    T key = current->getData();
    typename DoubleLinkedList<T>::Position mover = current->getPrev();

    while (mover != this->header && cmp(mover->getData(), key) > 0) {
      mover->getNext()->setData(mover->getData());
      mover = mover->getPrev();
    }

    mover->getNext()->setData(key);
    current = current->getNext();
  }
}

template <class T>
void DoubleLinkedList<T>::sortDataSelect(int cmp(const T&, const T&)) {
  if (this->isEmpty() || this->header->getNext()->getNext() == this->header)
    return;

  Position current = this->header->getNext();
  while (current != this->header) {
    Position minNode = current;
    Position scanner = current->getNext();

    while (scanner != this->header) {
      if (cmp(scanner->getData(), minNode->getData()) < 0)
        minNode = scanner;

      scanner = scanner->getNext();
    }

    if (minNode != current)
      this->swapData(minNode, current);

    current = current->getNext();
  }
}

template <class T>
void DoubleLinkedList<T>::sortDataShell(int cmp(const T&, const T&)) {
  int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                  34,   21,   13,   8,   5,   3,   2,   1,   0};

  int size = 0;
  Position temp = this->getFirstPos();
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
void DoubleLinkedList<T>::sortDataQuick(int(cmp)(const T&, const T&)) {
  if (this->isEmpty()) 
    return;
  this->quicksortRecursive(this->getFirstPos(), this->getLastPos(), cmp);
}

template <class T>
void DoubleLinkedList<T>::quicksortRecursive(Position low, Position high,
                                 int(cmp)(const T&, const T&)) {
  if (low == nullptr || high == nullptr || low == this->header ||
      high == this->header || low == high) {
    return;
  }

  Position pivot = this->partition(low, high, cmp);

  this->quicksortRecursive(low, pivot->getPrev(), cmp);
  this->quicksortRecursive(pivot->getNext(), high, cmp);
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::partition(Position low, Position high,
                                          int(cmp)(const T&, const T&)) {
  T pivotValue = high->getData();
  Position i = low->getPrev();

  for (Position j = low; j != high; j = j->getNext()) {
    if (cmp(j->getData(), pivotValue) < 0) {
      i = (i == this->header) ? this->getFirstPos() : i->getNext();
      this->swapData(i, j);
    }
  }

  i = (i == this->header) ? this->getFirstPos() : i->getNext();
  this->swapData(i, high);

  return i;
}

template <class T>
typename DoubleLinkedList<T>::Position DoubleLinkedList<T>::getNodeAt(int index) const {
  if (this->totalElements < index || index < 0)
    throw DataContainersExceptions::InvalidPosition();

  Position current = this->header->getNext();
  int count = 0;

  while (current != this->header && count < index) {
    current = current->getNext();
    count++;
  }

  return current;
}

template <class X>
std::ostream& operator<<(std::ostream& os, const DoubleLinkedList<X>& DoubleLinkedList) {
  typename DoubleLinkedList<X>::Position aux = DoubleLinkedList.header->getNext();

  while (aux != DoubleLinkedList.header) {
    os << aux->getData();
    aux = aux->getNext();
  }

  return os;
}

template <class X>
std::istream& operator>>(std::istream& is, DoubleLinkedList<X>& DoubleLinkedList) {
  X element;
  try {
    while (is >> element) {
      DoubleLinkedList.insertSortedData(element);
    }
  } catch (const std::invalid_argument& ex) {
  }

  return is;
}
#endif  // __DoubleLinkedList_H__