#ifndef __LIST_H__
#define __LIST_H__

#include <string>
#include <exception>

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
        void copyAll(const List<T>&);

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

        void sortData();
        void deleteAll();

        List<T>& operator = (const List<T>&);
};

//Implementación
    //Node
template<class T>
List<T>::Node::Node() {}

template<class T>
List<T>::Node::Node(const T& element) : this->data(element){}

template<class T>
T& List<T>::Node::getData(){
    return this->T;
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
        if(aux == p){
            return true;
        }   
        aux = aux->getNext();     
    }

    return false;
}

template <class T>
void List<T>::copyAll(const List<T>& other){
    //PENDIENTE
}

template <class T>
List<T>::List(){}

template <class T>
List<T>::List(const List<T>& other){
    this->copyAll(other);
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
    if( p != nullptr && !this->isValidPosition(position))
        throw std::exception("Posicion Invalida");
    
    Position newNode(new Node(element));
    if(newNode == nullptr)
        throw std::exception("Memoria no Disponible");
    
    if(position == nullptr){ //Insertar al Principio
        newNode->setNext(this->anchor);
        this->anchor = newNode;
    }

    else{ //Cualquier otra
        newNode->setNext(position->setNext(position->getNext()));
        this->getPrevPos(position);
    }

}

template <class T>
void List<T>::deleteData(const typename List<T>::Position& position){
    if(!this->isValidPosition(position))
        throw std::exception("Posicion Invalida");
    
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
typename List<T>::Position List<T>::getPrevPos(const typename List<T>::Position&) const{
    Position aux(this->anchor);

    while(aux != nullptr && aux->getNext() != Position)
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
        throw std::exception("Posicion Invalida");
    return p->getData();
}

template <class T>
string List<T>::toString() const{
    string result;
    Position aux(this->anchor);

    while(aux != nullptr){
        result += aux->getData()->toString();
        aux = aux->getNext();
    }

    return result;
}

template <class T>
void List<T>::sortData(){
    //PENDIENTE
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
List<T>& List<T>::operator = (const List<T>& other){
    this->copyAll(other);

    return *this;
}


#endif // __LIST_H__