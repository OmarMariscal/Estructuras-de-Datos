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
        Position getNodeAt(int) const;

        Position anchor = nullptr;

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
List<T>::Node::Node(const T& element) : data(element){}

template<class T>
T& List<T>::Node::getData(){
    return this->data;
}

template<class T>
typename List<T>::Position List<T>::Node::getNext() const{
    return this->next;
}

template<class T>
void List<T>::Node::setData(const T& data){
    this->data = data;
}

template<class T>
void List<T>::Node::setNext(const typename List<T>::Position& pointer){
    this->next = pointer;
}


//Lista

template <class T>
bool List<T>::isValidPosition(const Position& pointer) const{
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
void List<T>::add(const List<T>& other){
    Position aux(other.anchor), lastInsert(this->getLastPos()), newNode(nullptr);


    while(aux != nullptr){
        newNode = new Node(aux->getData());
        if(newNode == nullptr)
            throw DataContainersExceptions::MemoryDeficiency("Memoria no Disponible");

        if(lastInsert == nullptr)
            this->anchor = newNode;
        else
            lastInsert->setNext(newNode);
        
        lastInsert = newNode;
        aux = aux->getNext();
    }

}

template <class T>
List<T>::List(){}

template <class T>
List<T>::List(const List<T>& other){
    this->add(other);
}

template <class T>
List<T>::~List(){
    this->deleteAll();
}

template <class T>
bool List<T>::isEmpty() const{
    return this->anchor == nullptr;
}

template <class T>
void List<T>::insertData(const typename List<T>::Position& position, const T& element){
    if( position != nullptr && !this->isValidPosition(position))
        throw DataContainersExceptions::InvalidPosition();
    
    Position newNode(new Node(element));
    if(newNode == nullptr)
        throw DataContainersExceptions::MemoryOverflow("Memoria No Disponible");
    
    if(position == nullptr){ //Insertar al Principio
        newNode->setNext(this->anchor);
        this->anchor = newNode;
    }

    else{ //Cualquier otra
        newNode->setNext(position->getNext());
        position->setNext(newNode);
    }

}

template <class T>
void List<T>::deleteData(const typename List<T>::Position& position){
    if(!this->isValidPosition(position))
        throw DataContainersExceptions::InvalidPosition();
    
    if(position == this->anchor) //Eliminar el primero
        this->anchor = position->getNext();
    
    else //Cualquier otra Posición
        this->getPrevPos(position)->setNext(position->getNext());
    
    delete position;
}

template <class T>
typename List<T>::Position List<T>::getFirstPos() const{
    return this->anchor;
}

template <class T>
typename List<T>::Position List<T>::getLastPos() const{
    if(this->isEmpty())
        return nullptr;
    
    Position aux (this->anchor);
    while(aux->getNext() != nullptr)
        aux = aux->getNext();

    return aux;
}


template <class T>
typename List<T>::Position List<T>::getPrevPos(const typename List<T>::Position& position) const{
    if(position == nullptr)
        return nullptr;

    Position aux(this->anchor);
    while(aux != nullptr && aux->getNext() != position)
        aux = aux->getNext();
    
    return aux;

}
template <class T>
typename List<T>::Position List<T>::getNextPos(const typename List<T>::Position& position) const{
   return this->isValidPosition(position) ? position->getNext() : nullptr;
}


template <class T>
typename List<T>::Position List<T>::findData(const T& dataSearched) const{
    Position aux(this->anchor);

    while(aux != nullptr && aux->getData() != dataSearched)
        aux = aux->getNext();
    return aux;
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
    Position aux(this->anchor);

    while(aux != nullptr){
        result += aux->getData()->toString() + "\n";
        aux = aux->getNext();
    }

    return result;
}


template <class T>
void List<T>::deleteAll(){
    Position aux;

    while(this->anchor != nullptr){
        aux = this->anchor;
        this->anchor = aux->getNext();
        delete aux;
    }
}


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
List<T>& List<T>::operator = (const List<T>& other){
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

#endif // __LIST_H__