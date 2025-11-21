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
                oss << this->centerText("Ingrese el comando " + this->insertColorText("'/r'", "red") + " para cancelar");
                oss << this->divider("-");
                if(!this->ingredientList.isEmpty()){
                    oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                    oss << this->ingredientList.toString() << endl;
                    oss << this->divider();
                }

                oss << this->insertColorText("    Ingrese el Nombre del Ingrediente: ", "cyan");
                
                while(true){
                    dataString = this->readLinePrompt(oss.str());
                    newIngredient.setNameInredient(dataString);

                    if(this->ingredientList.findData(newIngredient) != nullptr)
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
    Ingredient searchedIngredient, aux;

    do{
            oss.str("");
            oss.clear();

            oss << this->windowHeader("🥑 RECETARIO DIGITAL - ELIMINAR INGREDIENTES");
            oss << this->centerText("Ingrese " + this->insertColorText("'/r'", "red") + "para regresar");
            oss << this->divider("-");

            if(!this->ingredientList.isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                oss << this->ingredientList.toString() << endl;
                oss << this->divider();
            }

                oss << this->insertColorText("    Ingrese el Nombre del Ingrediente a Eliminar: ", "cyan") << endl;            
                try{
                dataString = this->readLinePrompt(oss.str());
                oss << dataString << endl;                
            } catch(const InputExceptions::OperationCanceledException& ex){
                this->errorMessage("Eliminación de Ingrediente Cancelado.\nAvanzando...");
                return;
            }
            searchedIngredient.setNameInredient(dataString);    

            oss << this->insertColorText("¿Esta Seguro que Desea Eliminar Este Ingrediente? (S/N): ", "yellow");
            op = this->readChar(oss.str(), "S,N");
            oss << op << endl;

            if(op == 'S'){
                try{
                    this->ingredientList.deleteData(this->ingredientList.findData(searchedIngredient));
                    oss << this->centerText(this->insertColorText("!Ingrediente Eliminado Con Exito!", "green"));
                } catch(const DataContainersExceptions::InvalidPosition& ex){
                    oss << "Ingrediente " << this->insertColorText("No Encontrado", "red") << endl;
                }
            }
            else{
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
    
    try{
        do{
                oss.str("");
                oss.clear();

                oss << this->windowHeader("🥐 RECETARIO DIGITAL - MODIFICAR INGREDIENTES");
                oss << this->centerText("Ingrese " + this->insertColorText("'/r'", "red") + "para regresar");
                oss << this->divider("-");
                
                oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                oss << this->ingredientList.toString() << endl;
                oss << this->divider();

                oss << this->insertColorText("    Ingrese el nombre del Ingrediente a Modificar: ", "cyan");
                dataString = this->readLinePrompt(oss.str());
                oss << dataString << endl;

                searched.setNameInredient(dataString);

                try{
                    Ingredient& found = this->ingredientList.retrieve(this->ingredientList.findData(searched));
                
                    oss << " 🖊️ Seleccione que Atributo Modificar" << endl;
                    oss << this->insertColorText("    [A] ", "cyan") << "Nombre del Ingrediente" << endl;
                    oss << this->insertColorText("    [B] ", "cyan") << "Cantidad del Ingrediente" << endl;
                    oss << this->insertColorText("    [C] ", "cyan") << "Unidad de Medida" << endl;
                    oss << this->insertColorText("Ingrese una Opción: ", "yellow");
                    atributeModify = this->readChar(oss.str(), "A,B,C");
                    oss << atributeModify << endl;

                    switch(atributeModify){
                        case 'A':
                            oss << this->insertColorText("    Ingrese el Nuevo Nombre del Ingrediente: ", "cyan");
                            dataString = this->readLinePrompt(oss.str());
                            oss << dataString << endl;
                            
                            searched = found;
                            this->ingredientList.deleteData(this->ingredientList.findData(searched));
                            searched.setNameInredient(dataString);
                            this->ingredientList.insertSortedData(searched);
                            break;
                        case 'B':
                            oss << this->insertColorText("    Ingrese la Nueva Cantidad del Ingrediente: ", "cyan");
                            dataFloat = this->readFloat(oss.str(),0,99999);
                            oss << dataFloat << endl;
                            found.setAmount(dataFloat);                        
                            break;
                        case 'C':
                            oss << this->insertColorText("    Ingrese la Nueva Unidad de Medida Ingrediente: ", "cyan");
                            dataString = this->readLinePrompt(oss.str());
                            oss << dataString << endl;
                            found.setUnit(dataString);                    
                            break;
                    }

                    oss << this->centerText(this->insertColorText("¡Modificación Hecha Con Exito!", "green"));

                } catch(const DataContainersExceptions::InvalidPosition& ex){
                    oss << "Ingrediente " << this->insertColorText("No Encontrado", "red") << endl;
                }

                oss << " ❌ ¿Desea Modificar Más Ingredientes? (S/N): ";
                op = this->readChar(oss.str(), "S,N");

        } while(op != 'N');       
    } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Operación Cancelada\nRegresando...");
    }
}

IngredientMenu::IngredientMenu() : ingredientList(*new SimpleLinkedList<Ingredient>), recipeName("default") {}

IngredientMenu::IngredientMenu(SimpleLinkedList<Ingredient>& l, const std::string& r) : ingredientList(l), recipeName(r) {}

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
