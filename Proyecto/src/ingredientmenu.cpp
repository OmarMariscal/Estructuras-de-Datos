#include "ingredientMenu.hpp"

using namespace std;

void IngredientMenu::addIngredients(){
    ostringstream oss;
    float dataFloat;
    char op;
    string dataString;
    Ingredient newIngredient;
    try{
    do{
                oss.str("");
                oss.clear();

                oss << this->windowHeader("🥑 RECETARIO DIGITAL - AÑADIENDO INGREDIENTES");
                if(!this->ingredientList.isEmpty()){
                    oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                    oss << this->ingredientList.toString() << endl;
                    oss << this->divider();
                }

                oss << this->insertColorText("    Ingrese el Nombre del Ingrediente: ", "cyan");
                
                while(true){
                    dataString = this->readLinePrompt(oss.str());
                    newIngredient.setNameInredient(dataString);

                    if(this->ingredientList.findDataL(newIngredient) != -1)
                        this->errorMessage("El Ingrediente Ya Esta en la Lista\nIntente Agregar Uno Nuevo");
                    else
                        break;
                }

                oss << dataString << endl;

                oss << this->insertColorText("    Ingrese la Cantidad que se Utiliza: ", "cyan");
                dataFloat = this->readFloat(oss.str(), 0.0, 9999);
                oss << dataFloat << endl;
                newIngredient.setAmount(dataFloat);

                oss << this->insertColorText("    Ingrese la Unidad de Medidad de la Cantidad: ", "cyan");
                dataString = readLinePrompt(oss.str());
                oss << dataString << endl;
                newIngredient.setUnit(dataString);
                
                this->ingredientList.insertSortedData(newIngredient);

                oss << this->divider("-");
                oss << "✅ ";
                oss << this->insertColorText("Ingrediente Añadido con Exito!", "green") << endl;
                oss << " 🥕 ¿Desea Añadir Más Ingredientes? (S/N): ";

                op = this->readChar(oss.str(), "S,N");

        } while(op != 'N');

    } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Agregado de Ingrediente Cancelado.\nAvanzando...");
        return;
    }
}

void IngredientMenu::deleteIngredients(){
    if(this->ingredientList.isEmpty()){
        this->errorMessage("La Lista de Ingredientes está Vacía.\nNo Hay que Eliminar");
        return;
    }

    ostringstream oss;
    char op;
    int dataInt;
    string dataString;
    Ingredient searchedIngredient;

    do{
            oss.str("");
            oss.clear();

            oss << this->windowHeader("🥑 RECETARIO DIGITAL - ELIMINAR INGREDIENTES");
            if(!this->ingredientList.isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                oss << this->ingredientList.toString() << endl;
                oss << this->divider();
            }
            oss << this->centerText("Ingrese 'fin' para regresar");
            oss << this->insertColorText("    Ingrese el Nombre del Ingrediente a Eliminar: ", "cyan") << endl;
            dataString = this->readLinePrompt(oss.str());

            searchedIngredient.setNameInredient(dataString);    
            dataInt = this->ingredientList.findDataL(searchedIngredient);

            if(dataInt == -1){
                oss << "Ingrediente " << this->insertColorText("No Encontrado", "red") << endl;
            }

            else{
                oss << this->insertColorText("¿Esta Seguro que Desea Eliminar Este Ingrediente? (S/N): ", "yellow");
                op = this->readChar(oss.str(), "S,N");
                if(op == 'S'){
                    this->ingredientList.deleteData(dataInt);
                    oss << this->centerText(this->insertColorText("!Ingrediente Eliminado Con Exito!", "green"));
                }
                else
                    oss << this->centerText(this->insertColorText("Eliminacion Cancelada", "red"));
            }

            oss << " ❌ ¿Desea Eliminar Más Ingredientes? (S/N): ";

            op = this->readChar(oss.str(), "S,N");

    } while(op != 'N' && !this->ingredientList.isEmpty());
 
}

void IngredientMenu::modifyIngredient(){
        if(this->ingredientList.isEmpty()){
            this->errorMessage("No Hay Ingredientes en Esta Receta\nRegresando...");
            return;
        }
    ostringstream oss;
    string dataString;
    char op, atributeModify;
    Ingredient searched;
    float dataFloat;
    int dataInt;
    
    try{
        do{
                oss.str("");
                oss.clear();

                oss << this->windowHeader("🥐 RECETARIO DIGITAL - MODIFICAR INGREDIENTES");
                
                oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                oss << this->ingredientList.toString() << endl;
                oss << this->divider();

                oss << this->insertColorText("    Ingrese el nombre del Ingrediente a Modificar: ", "cyan");
                
                dataString = this->readLinePrompt(oss.str());
                searched.setNameInredient(dataString);
                dataInt = this->ingredientList.findDataL(searched);

                if(dataInt == -1){
                    oss << "Ingrediente " << this->insertColorText("No Encontrado", "red") << endl;
                }

                else{
                    oss << " 🖊️ Seleccione que Atributo Modificar" << endl;
                    oss << this->insertColorText("    [A] ", "cyan") << "Nombre del Ingrediente" << endl;
                    oss << this->insertColorText("    [B] ", "cyan") << "Cantidad del Ingrediente" << endl;
                    oss << this->insertColorText("    [C] ", "cyan") << "Unidad de Medida" << endl;
                    
                    atributeModify = this->readChar(oss.str(), "A,B,C");

                    switch(atributeModify){
                        case 'A':
                            oss << this->insertColorText("    Ingrese el Nuevo Nombre del Ingrediente: ", "cyan");
                            dataString = this->readLinePrompt(oss.str());
                            this->ingredientList.retrieve(dataInt)->setNameInredient(dataString);
                            break;
                        case 'B':
                            oss << this->insertColorText("    Ingrese la Nueva Cantidad del Ingrediente: ", "cyan");
                            dataFloat = this->readFloat(oss.str(),0,99999);
                            this->ingredientList.retrieve(dataInt)->setAmount(dataFloat);                        
                            break;
                        case 'C':
                            oss << this->insertColorText("    Ingrese la Nueva Unidad de Medida Ingrediente: ", "cyan");
                            dataString = this->readLinePrompt(oss.str());
                            this->ingredientList.retrieve(dataInt)->setUnit(dataString);                    
                            break;
                    }

                    oss << this->centerText(this->insertColorText("¡Modificación Hecha Con Exito!", "green"));
                }

                oss << " ❌ ¿Desea Modificar Más Ingredientes? (S/N): ";

                op = this->readChar(oss.str(), "S,N");

        } while(op != 'N');       
    } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Operación Cancelada\nRegresando...");
    }
}

IngredientMenu::IngredientMenu() : ingredientList(*new List<Ingredient, Configure::maximunIngredientSize>), recipeName("default") {}

IngredientMenu::IngredientMenu(List<Ingredient, Configure::maximunIngredientSize>& l, const std::string& r) : ingredientList(l), recipeName(r) {}

IngredientMenu::IngredientMenu(const IngredientMenu& other) : ingredientList(other.ingredientList), recipeName(other.recipeName) {}

void IngredientMenu::mainMenu() {
    if(this->ingredientList.isEmpty()){
        this->errorMessage("No hay Ingredientes Registrados\nRegresando...");
        return;
    }
    ostringstream oss;
    char op;

    do{
        oss.str("");
        oss.clear();
        
        oss << this->windowHeader("RECETARIO DIGITAL - MODIFICAR LISTA DE INGREDIENTES");
        oss << this->ingredientList.toString();
        oss << this->divider("-");
        oss << this->insertColorText("    [A] ", "cyan") << "Agregar Ingredientes" << endl;
        oss << this->insertColorText("    [B] ", "cyan") << "Eliminar Ingredientes" << endl;
        oss << this->insertColorText("    [C] ", "cyan") << "Modificar Ingredientes" << endl;
        oss << this->insertColorText("    [R] ", "cyan") << "Regresar" << endl; 
        oss << "Ingrese una Opción: ";
        op = this->readChar(oss.str(), "A,B,C,R");
        switch(op){
            case 'A':
                this->addIngredients();
                break;
            case 'B':
                this->deleteIngredients();
                break;
            case 'C':
                this->modifyIngredient();
                break;
        }
    } while(op != 'R');

}
