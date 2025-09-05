#ifndef __USERINTERFACE_H__
#define __USERINTERFACE_H__

#include "list.hpp"
#include "student.hpp"

#include <string>
#include <fstream>
#include <iostream>

class UserInterface{
    private:
        List<Student>* myListRef;

        void mainMenu();

        void addStudent();

        void delStudent();

        void showList();

        void writeToDisk();

        void readFromDisk();

        void enterToContinue();
    public:
        UserInterface(List<Student>&);


};


#endif // __USERINTERFACE_H__