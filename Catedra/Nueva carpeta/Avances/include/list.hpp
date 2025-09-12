#ifndef __LIST_H__
#define __LIST_H__

#include <string>
#include <exception>

using namespace std;

template<class T, int ARRAYSIZE = 1024>
class List{
    private:
        T data[ARRAYSIZE];
        int last;

        bool isValidPos(const int&) const;
        void copyAll(const List<T>&);
    public:
        List<T>();
        List<T>(const List<T>&);

        bool isEmpty() const;

        bool isFull() const;

        /// @brief 
        /// @param Posicion 
        /// @param  Elemento
        void insertData(const int&, const T&); 

        /// @brief 
        /// @param Posicion 
        void deleteData(const int&);

        int getFirstPos() const;

        int getLastPos() const;

        int getPrevPos(const int&) const;

        int getNextPos(const int&) const;

        int findData(const T&) const;

        /// @brief 
        /// @param Posicion 
        /// @return 
        T& retrieve(const int&);

        void sortData();

        std::string toString() const;

        void deleteAll();

        List<T, ARRAYSIZE>& operator=(const List<T, ARRAYSIZE>&);
};


template <class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isValidPos(const int& position) const{
    return position >= 0 and position <= this->last;

}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::copyAll(const List<T>& other){
    int i = 0;

    while(i <= this->last){
        this->data[i] = other.data[i];
        i++;
    }
    this->last = other.last;
}

template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List() : last(-1){}

template<class T, int ARRAYSIZE>
List<T, ARRAYSIZE>::List(const List<T>& other){
    this->copyAll(other);
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isEmpty() const{
    return this->last == -1;
}

template<class T, int ARRAYSIZE>
bool List<T, ARRAYSIZE>::isFull() const{
    return this->last == 499;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::insertData(const int& position, const T& element){
    if(this->isFull()){
        //Problema: Error
        //Desbordamiento de Datos, INsert Data
    }

    if(position != -1 || this->isValidPos(position)){
        //Problema
        //Posicion Invalida InsertData
    }

    int i = this->last++;

    while(i > position){
        this->data[i+1] = this->data[i];
        i++;
    }


}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteData(const int& position){
    if(isValidPos(position)){
        //Problema
        //Posición Invalida, DeleteData
    }    

    int i(position);

    while(i < this->last){
        this->data[i] = this->data[i + 1];
        i++;
    }
    this->last--;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getFirstPos() const{
    return isEmpty() ? -1 : 0;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getLastPos() const{
    return this->last;
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getPrevPos(const int& position) const{
    return (position == 0 || this->isValidPos(position)) ? -1 : (position - 1);
}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::getNextPos(const int& position) const{
    return (position == this->last || this->isValidPos(position)) ? -1 : (position + 1);

}

template<class T, int ARRAYSIZE>
int List<T, ARRAYSIZE>::findData(const T&) const{
    //Pendiente
}

template<class T, int ARRAYSIZE>
T& List<T, ARRAYSIZE>::retrieve(const int& position){
    if(this->isValidPos(position)){
        //Problema
        //Posicion Invalida, Retrieve    
    }

    return this->data[position];
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::sortData(){
    //Pendiente
}

template<class T, int ARRAYSIZE>
string List<T, ARRAYSIZE>::toString() const{
    string result;

    int i (0);

    while( i <= this->last){
        result += this->data[i].toString + "\n";

        i++;
    }    

    return result;
}

template<class T, int ARRAYSIZE>
void List<T, ARRAYSIZE>::deleteAll(){
    this->last = -1;
}

template<class T, int ARRAYSIZE>
List<T,ARRAYSIZE>& List<T, ARRAYSIZE>::operator=(const List<T, ARRAYSIZE>& other){
    this->copyAll(other);

    return *this;
}



#endif // __LIST_H__