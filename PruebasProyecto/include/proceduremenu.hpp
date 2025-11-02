#ifndef __PROCEDUREMENU_H__
#define __PROCEDUREMENU_H__

#include <string>
#include <sstream>

#include "basemenu.hpp"
#include "simplelinkedlist.hpp"
#include "stringwrapped.hpp"
#include "ownexceptions.hpp"
#include "configure.hpp"


class ProcedureMenu : protected BaseMenu{
    private:
        SimpleLinkedList<StringWrapper>& process;
        std::string recipeName;
    public:
        ProcedureMenu();
        ProcedureMenu(SimpleLinkedList<StringWrapper>&, const std::string&);
        ProcedureMenu(const ProcedureMenu&);

        void mainMenu();
        void addProcedure();
        void deleteProcedure();
        void editProcedure();
};

#endif // __PROCEDUREMENU_H__