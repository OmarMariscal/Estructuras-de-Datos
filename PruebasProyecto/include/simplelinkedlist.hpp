#ifndef __SIMPLELINKEDLIST_H__
#define __SIMPLELINKEDLIST_H__

#include <string>
#include <sstream>
#include "../lib/nlohmann/json.hpp"

#include "ownexceptions.hpp"

using namespace std;

//Definición
template <class T>
class SimpleLinkedList{
    class Node;

    public:
        typedef Node* Position;

    private:
        class Node{
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
        void add(const SimpleLinkedList<T>&);
        void simpleInsertData(const Position&, const T&);
        void updateTail():

        Position anchor = nullptr;
        Position tail = nullptr;           
        int totalElements = 0;

    public:
        SimpleLinkedList();
        SimpleLinkedList(const SimpleLinkedList<T>&);

        ~SimpleLinkedList();

        bool isEmpty() const;

        void insertData(const Position&, const T&);
        void insertLastData(const T&);
        void insertSortedData(const T&);


        void deleteData(const Position&);
        
        int getTotalElements() const;
        Position getFirstPos() const;
        Position getLastPos() const;
        Position getPrevPos(const Position&) const;
        Position getNextPos(const Position&) const;
        Position getNodeAt(const int&);

        Position findData(const T&) const;
        T& retrieve(const Position&);
        T& retrieve(const int&);

        string toString() const;
        string toString(const bool&) const;

        void sortDataBubble();
        void sortDataInsert();
        void sortDataSelect();
        void sortDataShell();

        void deleteAll();

        nlohmann::json toJson() const;
        void fromJson(const nlohmann::json&);

        SimpleLinkedList<T>& operator = (const SimpleLinkedList<T>&);

        void sortDataBubble(int(const T&, const T&));
        void sortDataInsert(int(const T&, const T&));
        void sortDataSelect(int(const T&, const T&));
        void sortDataShell(int(const T&, const T&));

        void insertSortedData(const T&, int(const T&, const T&));
};

//Implementación
    //Node
template<class T>
SimpleLinkedList<T>::Node::Node() {}

template<class T>
SimpleLinkedList<T>::Node::Node(const T& element) : data(element){}

template<class T>
T& SimpleLinkedList<T>::Node::getData(){
    return this->data;
}

template<class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::Node::getNext() const{
    return this->next;
}

template<class T>
void SimpleLinkedList<T>::Node::setData(const T& data){
    this->data = data;
}

template<class T>
void SimpleLinkedList<T>::Node::setNext(const typename SimpleLinkedList<T>::Position& pointer){
    this->next = pointer;
}


//SimpleLinkedLista

template <class T>
bool SimpleLinkedList<T>::isValidPosition(const Position& pointer) const{
    Position aux = this->anchor;

    while(aux != nullptr){
        if(aux == pointer){
            return true;
        }   
        aux = aux->getNext();     
    }

    return false;
}

template <class T>
void SimpleLinkedList<T>::add(const SimpleLinkedList<T>& other){
    Position aux = other.anchor;
    Position lastInsert = this->tail; 
    Position newNode = nullptr;

    while(aux != nullptr){
        newNode = new (nothrow) Node(aux->getData());
        if(newNode == nullptr)
            throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

        if(lastInsert == nullptr) {       
            this->anchor = newNode;
        } else {
            lastInsert->setNext(newNode);
        }
        
        lastInsert = newNode;
        aux = aux->getNext();
        this->totalElements++;
    }

    if (lastInsert != nullptr)
        this->tail = lastInsert;
}

template <class T>
void SimpleLinkedList<T>::simpleInsertData(const Position& prev, const T& e){  

    Position newNode = new (nothrow) Node(e);
    if (newNode == nullptr)
        throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");    

    if(prev == nullptr){ 
        newNode->setNext(this->anchor);
        this->anchor = newNode;
        if (this->tail == nullptr)
            this->tail = newNode;
    }
    else{ 
        if (!this->isValidPosition(prev)) {
            delete newNode;
            throw DataContainersExceptions::InvalidPosition();
        }

        newNode->setNext(prev->getNext());
        prev->setNext(newNode);

        if (prev == this->tail)
            this->tail = newNode;
    }

    this->totalElements++;
}

template <class T>
void SimpleLinkedList<T>::updateTail(){
    Position aux(this->anchor);
    if(aux == nullptr){
        this->tail = nullptr;
        return;
    }

    while(aux->getNext() != nullptr)
        aux = aux->getNext();
    
    this->tail = aux;
}


template <class T>
SimpleLinkedList<T>::SimpleLinkedList() : anchor(nullptr), tail(nullptr), totalElements(0) {}

template <class T>
SimpleLinkedList<T>::SimpleLinkedList(const SimpleLinkedList<T>& other) : anchor(nullptr), tail(nullptr), totalElements(0){
    this->add(other);
}

template <class T>
SimpleLinkedList<T>::~SimpleLinkedList(){
    this->deleteAll();
}

template <class T>
bool SimpleLinkedList<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template <class T>
void SimpleLinkedList<T>::insertData(const typename SimpleLinkedList<T>::Position& position, const T& element){
    if( position != nullptr && !this->isValidPosition(position))
        throw DataContainersExceptions::InvalidPosition();
    
    this->simpleInsertData(position, element);
}

template <class T>
void SimpleLinkedList<T>::insertLastData(const T& e){
    this->simpleInsertData(this->tail, e);
}

template <class T>
void SimpleLinkedList<T>::insertSortedData(const T& e){
    Position aux(this->anchor), prevPos(nullptr);

    while(aux != nullptr && e > aux->getData())
        aux = (prevPos = aux)->getNext();

    this->simpleInsertData(prevPos, e);
}

template <class T>
void SimpleLinkedList<T>::deleteData(const typename SimpleLinkedList<T>::Position& position){
    if(position == nullptr || !this->isValidPosition(position))
        throw DataContainersExceptions::InvalidPosition();
    
    if(position == this->anchor) { 
        this->anchor = position->getNext();
        if (position == this->tail)
            this->tail = this->anchor; 

    } else { 
        Position prev = this->getPrevPos(position);
        prev->setNext(position->getNext());

        if (position == this->tail)
            this->tail = prev;
    }
    
    delete position;
    this->totalElements--;
}

template <class T>
int SimpleLinkedList<T>::getTotalElements() const{
    return this->totalElements;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getFirstPos() const{
    return this->anchor;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getLastPos() const{
    return this->tail; 
}


template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getPrevPos(const typename SimpleLinkedList<T>::Position& position) const{
    if(position == nullptr)
        return nullptr;

    Position aux(this->anchor);
    while(aux != nullptr && aux->getNext() != position)
        aux = aux->getNext();
    
    return aux;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getNextPos(const typename SimpleLinkedList<T>::Position& position) const{
   return this->isValidPosition(position) ? position->getNext() : nullptr;
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::findData(const T& dataSearched) const{
    Position aux(this->anchor);

    while(aux != nullptr && aux->getData() != dataSearched)
        aux = aux->getNext();
    return aux;
}

template <class T>
T& SimpleLinkedList<T>::retrieve(const typename SimpleLinkedList<T>::Position& p){
    if(p == nullptr || !this->isValidPosition(p))
        throw DataContainersExceptions::InvalidPosition();
    return p->getData();
}

template <class T>
T& SimpleLinkedList<T>::retrieve(const int& pos){
    if(pos < 0 || pos >= this->totalElements)
        throw DataContainersExceptions::InvalidPosition();

    Position aux(this->anchor);
    int i = 0;
    while (i < pos) {
        aux = aux->getNext();
        ++i;
    }

    return aux->getData();
}

template <class T>
string SimpleLinkedList<T>::toString() const{
    string result;
    Position aux(this->anchor);

    while(aux != nullptr){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
    }

    return result;
}

template <class T>
std::string SimpleLinkedList<T>::toString(const bool& numered) const {
    Position aux(this->anchor);
    std::ostringstream oss;
    int i(1);
  while(aux != nullptr){
    if(numered)
      oss << i++ << ". "; 
    oss << aux->getData().toString() << std::endl;
    aux = aux->getNext();
  } 
  
  return oss.str();
}


template <class T>
void SimpleLinkedList<T>::deleteAll(){
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;
        this->anchor = aux->getNext();
        delete aux;
    }

    this->anchor = nullptr;
    this->tail = nullptr;
    this->totalElements = 0;
}


template <class T>
void SimpleLinkedList<T>::sortDataBubble (){
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
void SimpleLinkedList<T>::sortDataInsert() {
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
        }
        else {
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
    this->updateTail();
}

template <class T>
void SimpleLinkedList<T>::sortDataSelect() {
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
void SimpleLinkedList<T>::sortDataShell() {
    if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
        return;
    }
    
    int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                    34,   21,   13,   8,   5,   3,   2,   1,   0};
    
    int size = this->totalElements;
    
    int pos = 0;
    int gap = series[pos];
    
    while (gap > size) {
        gap = series[++pos];
    }
    
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            Position nodeI = this->getNodeAt(i);
            if (nodeI == nullptr) continue;
            T tempData = nodeI->getData();
            
            int j = i;
            while (j >= gap) {
                Position nodeJMinusGap = this->getNodeAt(j - gap);
                if (nodeJMinusGap == nullptr) break;
                
                if (nodeJMinusGap->getData() > tempData) {
                    Position nodeJ = this->getNodeAt(j);
                    if (nodeJ == nullptr) break;
                    nodeJ->setData(nodeJMinusGap->getData());
                    j -= gap;
                } else {
                    break;
                }
            }
            
            Position nodeJ = this->getNodeAt(j);
            if (nodeJ != nullptr)
                nodeJ->setData(tempData);
        }
        
        gap = series[++pos];
    }
}

template <class T>
nlohmann::json SimpleLinkedList<T>::toJson() const{
    Position aux(this->anchor);
    nlohmann::json j;
    j["data"] = nlohmann::json::array();
    while(aux != nullptr){
        j["data"].push_back(aux->getData().toJson());
        aux = aux->getNext();
    }
    return j;
}

template <class T>
void SimpleLinkedList<T>::fromJson(const nlohmann::json& js){
    this->deleteAll();

    if (!js.is_object() || !js.contains("data") || !js["data"].is_array())
        throw DataContainersExceptions::InvalidJsonFormat();

    Position last = nullptr;
    for (const auto& item : js["data"]) {
        T obj;                
        obj.fromJson(item);  
        this->simpleInsertData(last, obj);
        if (last == nullptr) {
            last = this->anchor;
        } else {
            last = last->getNext();
        }
    }
}

template <class T>
SimpleLinkedList<T>& SimpleLinkedList<T>::operator = (const SimpleLinkedList<T>& other){
    if (this == &other) return *this;
    this->deleteAll();
    this->add(other);
    return *this;
}

template <class T>
void SimpleLinkedList<T>::sortDataBubble(int cmp(const T&, const T&)) {
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
void SimpleLinkedList<T>::sortDataInsert(int cmp(const T&, const T&)) {
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
        }
        else {
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
    
    this->updateTail();
}

template <class T>
void SimpleLinkedList<T>::sortDataSelect(int cmp(const T&, const T&)) {
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
void SimpleLinkedList<T>::sortDataShell(int cmp(const T&, const T&)) {
    if (this->anchor == nullptr || this->anchor->getNext() == nullptr) {
        return;
    }
    
    int series[] = {4181, 2584, 1597, 987, 610, 377, 233, 144, 89, 55,
                    34,   21,   13,   8,   5,   3,   2,   1,   0};
    
    int size = this->totalElements;
    
    int pos = 0;
    int gap = series[pos];
    
    while (gap > size) {
        gap = series[++pos];
    }
    
    while (gap > 0) {
        for (int i = gap; i < size; i++) {
            Position nodeI = this->getNodeAt(i);
            if (nodeI == nullptr) continue;
            T tempData = nodeI->getData();
            
            int j = i;
            while (j >= gap) {
                Position nodeJMinusGap = this->getNodeAt(j - gap);
                if (nodeJMinusGap == nullptr) break;
                
                if (cmp(nodeJMinusGap->getData(), tempData) > 0) {
                    Position nodeJ = this->getNodeAt(j);
                    if (nodeJ == nullptr) break;
                    nodeJ->setData(nodeJMinusGap->getData());
                    j -= gap;
                } else {
                    break;
                }
            }
            
            Position nodeJ = this->getNodeAt(j);
            if (nodeJ != nullptr)
                nodeJ->setData(tempData);
        }
        
        gap = series[++pos];
    }
}

template <class T>
typename SimpleLinkedList<T>::Position SimpleLinkedList<T>::getNodeAt(const int& index) {
    if(index < 0 || index >= this->totalElements)
        throw DataContainersExceptions::InvalidPosition();
    
    Position current = this->anchor;
    int count = 0;
    
    while (current != nullptr && count < index) {
        current = current->getNext();
        count++;
    }
    
    return current;
}

template <class T>
void SimpleLinkedList<T>::insertSortedData(const T& e, int cmp(const T&, const T&)){
    Position aux(this->anchor), prevPos(nullptr);

    while(aux != nullptr && cmp(e, aux->getData()) > 0)
        aux = (prevPos = aux)->getNext();
    
    this->simpleInsertData(prevPos, e);
}

#endif // __SIMPLELINKEDLIST_H__
