#ifndef __PROCEDUREMENU_H__
#define __PROCEDUREMENU_H__

#include "list.hpp"
#include "stringwrapped.hpp"

class ProcedureMenu{
    private:
        List<StringWrapper, Configure::maximunIngredientSize>& process;
        std::string recipeName;

        void mainMenu();
        void addProcedure();
        void deleteProcedure();
        void editProcedure();
    public:
        ProcedureMenu();
        ProcedureMenu(const List<StringWrapper, Configure::maximunIngredientSize>&, const std::string&);
        ProcedureMenu(const ProcedureMenu&);
};

#endif // __PROCEDUREMENU_H__