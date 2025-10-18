#include "proceduremenu.hpp"

using namespace std;

void ProcedureMenu::mainMenu(){
    if(this->process.isEmpty()){
        this->errorMessage("No hay Pasos Registrados\nRegresando...");
        return;
    }
    ostringstream oss;
    char op;

    do{
        oss.str("");
        oss.clear();
        
        oss << this->windowHeader("RECETARIO DIGITAL - MODIFICAR LISTA DE PASOS");
        oss << this->process.toString(true);
        oss << this->divider("-");
        oss << this->insertColorText("    [A] ", "cyan") << "Agregar Pasos" << endl;
        oss << this->insertColorText("    [B] ", "cyan") << "Eliminar Pasos" << endl;
        oss << this->insertColorText("    [C] ", "cyan") << "Modificar Pasos" << endl;
        oss << this->insertColorText("    [R] ", "cyan") << "Regresar" << endl; 
        oss << "Ingrese una Opción: ";
        op = this->readChar(oss.str(), "A,B,C,R");
        switch(op){
            case 'A':
                this->addProcedure();
                break;
            case 'B':
                this->deleteProcedure();
                break;
            case 'C':
                this->editProcedure();
                break;
        }
    } while(op != 'R');
}



void ProcedureMenu::addProcedure(){
    ostringstream oss;
    char op;
    string dataString;
    StringWrapper newStep;
    try{
    do{
            oss.str("");
            oss.clear();

            oss << this->windowHeader("🥑 RECETARIO DIGITAL - AÑADIENDO PASOS");
            if(!this->process.isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Pasos Actual para " + recipeName, "magenta"));
                oss << this->process.toString(true) << endl;
                oss << this->divider();
            }
            oss << this->insertColorText("    Ingrese '/r' para Cancelar", "red") << endl;
            oss << this->insertColorText("    Ingrese el Nuevo Paso Para La Receta: ", "cyan");
            newStep = this->readLinePrompt(oss.str());


            oss << newStep << endl;
            
            this->process.insertElement(newStep, this->process.getLastPosition()+1);

            oss << this->divider("-");
            oss << "✅ ";
            oss << this->insertColorText("Paso Añadido con Exito!", "green") << endl;
            oss << " 🥕 ¿Desea Añadir Más Pasos? (S/N): ";

            op = this->readChar(oss.str(), "S,N");

    } while(op != 'N');
    } catch (const InputExceptions::OperationCanceledException&){
        this->errorMessage("Operación Cancelada.\nRegresando...");
        return;
    }
}

void ProcedureMenu::deleteProcedure(){
    if(this->process.isEmpty()){
        this->errorMessage("La Lista de Pasos está Vacía.\nNo Hay que Eliminar");
        return;
    }

    ostringstream oss;
    char op;
    int dataInt;
    string dataString;
    StringWrapper searchedStep;
    
    do{
            oss.str("");
            oss.clear();

            oss << this->windowHeader("🥑 RECETARIO DIGITAL - ELIMINAR PASOS");
            if(!this->process.isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Pasos Actual para " + recipeName, "magenta"));
                oss << this->process.toString(true) << endl;
                oss << this->divider();
            }
            oss << this->centerText("Ingrese 'fin' para regresar");
            oss << this->insertColorText("    Ingrese el Número del Paso a Eliminar: ", "cyan");
            
            while(true){
                try{
                    dataString = this->readLinePrompt(oss.str());
                    if( this->standarString(dataString) == "FIN"){
                        oss << this->centerText(this->insertColorText("Regresando...", "blue"));
                        return;
                    }

                    dataInt = stoi(dataString) - 1;
                
                    this->process.retrieve(dataInt);
                    oss << dataInt << endl;
                    oss << this->insertColorText("¿Esta Seguro que Desea Eliminar Este Ingrediente? (S/N): ", "yellow");
                    op = this->readChar(oss.str(), "S,N");
                    oss << op << endl;
                    if(op == 'S'){
                        this->process.deleteData(dataInt);
                        oss << this->centerText(this->insertColorText("!Paso Eliminado Con Exito!", "green"));
                    }
                    else
                        oss << this->centerText(this->insertColorText("Eliminacion Cancelada", "red"));
                break;
                } catch(const DataContainersExceptions::InvalidPosition& ex){
                    oss << this->centerText(this->insertColorText("Posición Inválida", "red"));
                } catch(const InputExceptions::OperationCanceledException& ex){
                    this->errorMessage("Operación Cancelada.\nRegresando...");
                    return;
                } catch(const invalid_argument& ex){
                    this->errorMessage("Entrada No Numérica\nInténtelo Nuevamente");
                }
        }
            oss << " ❌ ¿Desea Eliminar Más Ingredientes? (S/N): ";

            op = this->readChar(oss.str(), "S,N");
        
    } while(op != 'N' && !this->process.isEmpty());

    this->errorMessage("Ya No Hay Pasos Registrados.\nRegresando...");
}

void ProcedureMenu::editProcedure(){
        if(this->process.isEmpty()){
            this->errorMessage("No Hay Ingredientes en Esta Receta\nRegresando...");
            return;
        }
    ostringstream oss;
    string dataString;
    char op;
    StringWrapper* searched;
    int dataInt;
    
    try{
        do{
                oss.str("");
                oss.clear();

                oss << this->windowHeader("🥐 RECETARIO DIGITAL - MODIFICAR PASOS");                
                oss << this->centerText("👍" + this->insertColorText("Lista de Pasos Actual para " + recipeName, "magenta"));
                oss << this->process.toString(true) << endl;
                oss << this->divider();
                oss << this->insertColorText("    Ingrese '/r' Para Cancelar", "red") << endl;
                oss << this->insertColorText("    Ingrese el Índice del Paso a Modificar: ", "cyan");
                
                dataInt = this->readInteger(oss.str(), 0, 999999);

                try{
                    searched = this->process.retrieve(dataInt - 1);
                    oss << this->insertColorText("v    Ingrese la Modificación para el Paso", "yellow");
                    *searched = this->readLinePrompt(oss.str());
                    oss << this->centerText(this->insertColorText("¡Modificación Hecha Con Exito!", "green"));
                } catch(const DataContainersExceptions::InvalidPosition& ex){
                    oss << this->centerText("Paso" + this->insertColorText("No Encontrado", "red"));
                }
    
                oss << " ❌ ¿Desea Modificar Más Ingredientes? (S/N): ";
                op = this->readChar(oss.str(), "S,N");

        } while(op != 'N');       
    } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Operación Cancelada\nRegresando...");
    }

}

ProcedureMenu::ProcedureMenu() : process(* new List<StringWrapper, Configure::maximunProcedureSize>), recipeName("default") {}
ProcedureMenu::ProcedureMenu(List<StringWrapper, Configure::maximunIngredientSize>& l, const std::string& r) : process(l), recipeName(r) {}
ProcedureMenu::ProcedureMenu(const ProcedureMenu& other) : process(other.process), recipeName(other.recipeName) {}