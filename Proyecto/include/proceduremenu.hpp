#ifndef __PROCEDUREMENU_H__
#define __PROCEDUREMENU_H__

#include <string>
#include <sstream>

#include "basemenu.hpp"
#include "list.hpp"
#include "stringwrapped.hpp"
#include "ownexceptions.hpp"
#include "configure.hpp"


class ProcedureMenu : protected BaseMenu{
    private:
        List<StringWrapper, Configure::maximunIngredientSize>& process;
        std::string recipeName;
    public:
        ProcedureMenu();
        ProcedureMenu(List<StringWrapper, Configure::maximunIngredientSize>&, const std::string&);
        ProcedureMenu(const ProcedureMenu&);

        void mainMenu();
        void addProcedure();
        void deleteProcedure();
        void editProcedure();
};

#endif // __PROCEDUREMENU_H__