#ifndef __LIST_H__
#define __LIST_H__

#include <string>
#include "ownexceptions.hpp"

using namespace std;

//Definición
template <class T>
class List{
    class Node;

    public:
        typedef Node* Position;

    private:
        class Node{
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
        void add(const List<T>&);
        Position getNodeAt(int) const;

        Position header = nullptr;

    public:
        List();
        List(const List<T>&);

        ~List();

        bool isEmpty() const;

        void insertData(const Position&, const T&);
        void deleteData(const Position&);
        Position getFirstPos() const;
        Position getLastPos() const;
        Position getPrevPos(const Position&) const;
        Position getNextPos(const Position&) const;

        Position findData(const T&) const;
        T& retrieve(const Position&);

        string toString() const;


        void sortDataBubble();
        void sortDataInsert();
        void sortDataSelect();
        void sortDataShell();

        void deleteAll();

        List<T>& operator = (const List<T>&);

        void sortDataBubble(int(const T&, const T&));
        void sortDataInsert(int(const T&, const T&));
        void sortDataSelect(int(const T&, const T&));
        void sortDataShell(int(const T&, const T&));

};

//Implementación
    //Node
template<class T>
List<T>::Node::Node() {}

template<class T>
List<T>::Node::Node(const T& element) : dataPtr(new T(element)){
    if(dataPtr == nullptr){
        throw NodeExceptions::NodeExceptionTo("Memoria no disponible, Node");
    }
}

template<class T>
List<T>::Node::~Node(){
    delete this->dataPtr;
}

template<class T>
T* List<T>::Node::getDataPtr(){
    return this->dataPtr;
}

template<class T>
T& List<T>::Node::getData(){
    if(this->dataPtr == nullptr)
        throw NodeExceptions::NodeExceptionTo("Dato Inexistente, getData");
    return *this->dataPtr;
}

template<class T>
typename List<T>::Position List<T>::Node::getPrev() const{
    return this->prev;
}

template<class T>
typename List<T>::Position List<T>::Node::getNext() const{
    return this->next;
}

template<class T>
void List<T>::Node::setDataPtr(T* p){
    this->dataPtr = p;
}

template<class T>
void List<T>::Node::setData(const T& e){
    if(this->dataPtr == nullptr)
        if(this->dataPtr = new T(e) == nullptr)
            throw NodeExceptions::NodeExceptionTo("Memoria no disponible, setData");
    else
        *this->dataPtr = e;
}

template<class T>
void List<T>::Node::setPrev(const typename List<T>::Position& pointer){
    this->prev = pointer;
}

template<class T>
void List<T>::Node::setNext(const typename List<T>::Position& pointer){
    this->next = pointer;
}


//Lista

template <class T>
bool List<T>::isValidPosition(const Position& pointer) const{
    Position aux (this->header->getNext());

    while(aux != header){
        if(aux == pointer){
            return true;
        }   
        aux = aux->getNext();     
    }

    return false;
}

template <class T>
void List<T>::add(const List<T>& other){
    Position aux(other.header->getNext()), newNode;


    while(aux != other.header){
    
        if(newNode = new Node(aux->getData()) == newNode == nullptr)
            throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

        newNode->setPrev(this->header->getPrev());
        newNode->setNext(this->header);

        this->header->getPrev()->setNext(newNode);
        this->header->setPrev(newNode);

        aux = aux->getNext();
    }

}

template <class T>
List<T>::List() : header(new Node) {
    if(this->header == nullptr)
        throw NodeExceptions::NodeExceptionTo("Memoria no Disponible, List");

    this->header->setPrev(this->header);
    this->header->setNext(this->header);
}

template <class T>
List<T>::List(const List<T>& other){
    this->add(other);
}

template <class T>
List<T>::~List(){
    this->deleteAll();

    delete this-header;

}

template <class T>
bool List<T>::isEmpty() const{
    return this->header->getNext() == this->header;
}

template <class T>
void List<T>::insertData(const typename List<T>::Position& position, const T& element){
    if( position != nullptr && !this->isValidPosition(position))
        throw DataContainersExceptions::InvalidPosition();

    Position newNode(new Node(element));
    if(newNode == nullptr)
        throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");
    
    Position insPos(position == nullptr ? header : position);

    newNode->setPrev(insPos);
    newNode->setNext(insPos->getNext());

    insPos->getNext()->setPrev(newNode);
    insPos->setNext(newNode);
}

template <class T>
void List<T>::deleteData(const typename List<T>::Position& position){
    if(!this->isValidPosition(position))
        throw DataContainersExceptions::InvalidPosition();
    
    position->getPrev()->setNext(position->getNext());
    position->getNext()->setPrev(position->getPrev());
    
    delete position;
}

template <class T>
typename List<T>::Position List<T>::getFirstPos() const{
    return this->isEmpty() ? nullptr : this->header->getNext();
}

template <class T>
typename List<T>::Position List<T>::getLastPos() const{
    return this->isEmpty() ? nullptr : this->header->getPrev(); 
}


template <class T>
typename List<T>::Position List<T>::getPrevPos(const typename List<T>::Position& position) const{
   return position == this->header->getNext() || !this->isValidPosition(position) ? nullptr : position->getPrev(); 
}

template <class T>
typename List<T>::Position List<T>::getNextPos(const typename List<T>::Position& position) const{
   return position == this->header->getPre() || !this->isValidPosition(position) ? nullptr : position->getNext();
}


template <class T>
typename List<T>::Position List<T>::findData(const T& dataSearched) const{
    Position aux(this->header->getNext());

    while(aux != this->header){
        if(aux->getData() == dataSearched)
            return aux;
        aux = aux->getNext();
    }

    return nullptr;
}

template <class T>
T& List<T>::retrieve(const typename List<T>::Position& p){
    if(!this->isValidPosition(p))
        throw DataContainersExceptions::InvalidPosition();
    return p->getData();
}

template <class T>
string List<T>::toString() const{
    string result;
    Position aux(this->header->getNext());

    while(aux != this->header){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
    }

    return result;
}


template <class T>
void List<T>::deleteAll(){
    Position aux;

    while(this->header->getNext() != this->header){
        aux = this->header->getNext();

        this->header->setNext(aux->getNext());
        delete aux;
    }

    this->header->setPrev(this->header);
}

template <class T>
List<T>& List<T>::operator = (const List<T>& other){
    this->deleteAll();
    this->add(other);

    return *this;
}

/*

template <class T>
void List<T>::sortDataBubble (){
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
*/

#endif // __LIST_H__