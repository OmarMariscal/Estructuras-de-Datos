#include "menu.hpp"

using namespace std;

int Menu::readInteger(std::string oss, const int& lowerLimit, const int& upperLimit) {

  string aux("");
  int result;
  while (true) {
    try {
      system("CLS");
      cout << oss;
      getline(cin, aux);

      if (aux == "/r")
        throw InputExceptions::OperationCanceledException("Cancelado por usuario");

      result = stoi(aux);

      if (result > upperLimit || result < lowerLimit)
        throw InputExceptions::InvalidOption("Numero Fuera de Rango");
      break;
    } catch (const InputExceptions::InvalidOption& ex) {
        this->errorMessage("Numero Fuera de Rango\nVuelva a Intentarlo");
    } catch (const invalid_argument& msg) {
        this->errorMessage("Entrada No Numérica\nAsegúrese de Ingresar Un Número Válido");
    }
  }

  return result;
}

float Menu::readFloat(const std::string& oss, const float& lowerLimit, const float& upperLimit) {
  std::string aux("");
  float result;
  while (true) {
    try {
      system("CLS");
      std::cout << oss;
      std::getline(std::cin, aux);

      if (aux == "/r")
        throw InputExceptions::InvalidOption("Cancelado por usuario");

      result = std::stof(aux);

      if (result > upperLimit || result < lowerLimit)
        throw InputExceptions::InvalidOption("Numero Fuera de Rango");
      break;
    } catch (const std::invalid_argument& ex) {
        this->errorMessage("Entrada Inválida\nInténtelo Nuevamente");
    } catch (const std::out_of_range& ex) {
      this->errorMessage("Entrada Fuera de Rango\nInténtelo Nuevamente");
    } catch (const InputExceptions::InvalidOption& msg) {
      system("CLS");
      std::cout << msg.what() << std::endl;
    }
  }

  return result;
}

Name Menu::readName(string prompt, const string& petition, const string& petition2) {
  Name result;
  prompt += petition;
  result.setFirst(readLinePrompt(prompt));
  prompt += result.getFirst() + "\n";
  prompt += petition2;
  result.setLast(readLinePrompt(prompt));

  return result;
}

string Menu::readLinePrompt(const string& prompt, bool allowEmpty) {
  string result;
  while (true) {
    system("CLS");
    cout << prompt;
    getline(cin, result);
    if(result == "/r")
        throw InputExceptions::OperationCanceledException();
    if (!allowEmpty && result.empty()) {
      system("CLS");
      this->errorMessage("No Puede Estar Vacío\nIntente Nuevamente.");
      continue;
    }
    return result;
  }
}

char Menu::readChar(const std::string& prompt, const std::string& options) {
    while (true) {
        this->cleanScreen();
        string input;
        cout << prompt;
        getline(cin, input);

        if (!input.empty()) {
            char result = toupper(input[0]);
            if (options.find(result) != string::npos)
                return result;
        }

        this->cleanScreen();
        this->errorMessage("La opcion ingresada es invalida.\nIntentelo nuevamente.");
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Category Menu::readCategory(const std::string& prompt){
    Category result;
    int op;
    op = this->readInteger(prompt, 1, 4);
    switch(op){
        case 1: result = DESAYUNO; break;
        case 2: result = COMIDA; break;
        case 3: result = CENA; break;
        case 4: result = NAVIDEÑO; break;
    }

    return result;
}

std::string Menu::standarString(std::string text){
    // Eliminar espacios al final
    size_t end = text.size();
    while (end > 0 && (text[end - 1] == ' ' || text[end - 1] == '\t')) {
        --end;
    }
    text.resize(end);

    // 2. Convertir a mayúsculas (solo letras ASCII)
    for (size_t i = 0; i < text.size(); ++i) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = text[i] - ('a' - 'A');
        }
    }

    return text;
}

std::string Menu::clearColor(const std::string& s){
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        if (c == 0x1B) { // ESC
            // si sigue '[', consumimos hasta una letra (final de secuencia CSI)
            if (i + 1 < s.size() && s[i + 1] == '[') {
                i += 2; // saltamos ESC and '['
                // consumir hasta encontrar una letra A-Z o a-z
                while (i < s.size()) {
                    unsigned char cc = static_cast<unsigned char>(s[i]);
                    if ((cc >= 'A' && cc <= 'Z') || (cc >= 'a' && cc <= 'z')) break;
                    ++i;
                }
                // al salir, i apunta a la letra final; el bucle for incrementará i,
                // por eso dejamos que continúe normalmente (se descarta la letra final también)
                continue;
            } else {
                // ESC sin '[', saltar el ESC solo
                continue;
            }
        }
        out.push_back(c);
    }
    return out;

}

void Menu::menuIngredints(List<Ingredient, Configure::maximunIngredientSize>* r, const string& recipeName){
    if(r->isEmpty()){
        this->errorMessage("No hay Ingredientes Registrados\nRegresando...");
        return;
    }
    ostringstream oss;
    char op;

    do{
        oss.str("");
        oss.clear();
        
        oss << this->windowHeader("RECETARIO DIGITAL - MODIFICAR LISTA DE INGREDIENTES");
        oss << r->toString();
        oss << this->divider("-");
        oss << this->insertColorText("    [A] ", "cyan") << "Agregar Ingredientes" << endl;
        oss << this->insertColorText("    [B] ", "cyan") << "Eliminar Ingredientes" << endl;
        oss << this->insertColorText("    [C] ", "cyan") << "Modificar Ingredientes" << endl;
        oss << this->insertColorText("    [R] ", "cyan") << "Regresar" << endl; 
        oss << "Ingrese una Opción: ";
        op = this->readChar(oss.str(), "A,B,C,R");
        switch(op){
            case 'A':
                this->addIngredients(r, recipeName);
                break;
            case 'B':
                this->deleteIngredients(r, recipeName);
                break;
            case 'C':
                this->modifyIngredient(r, recipeName);
                break;
        }
    } while(op != 'R');
}

void Menu::addIngredients(List<Ingredient, Configure::maximunIngredientSize>* r, const string& recipeName){
    ostringstream oss;
    float dataFloat;
    char op;
    string dataString;
    Ingredient newIngredient;
    do{
            oss.str("");
            oss.clear();

            oss << this->windowHeader("🥑 RECETARIO DIGITAL - AÑADIENDO INGREDIENTES");
            if(!r->isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                oss << r->toString() << endl;
                oss << this->divider();
            }

            oss << this->insertColorText("    Ingrese el Nombre del Ingrediente: ", "cyan");
            
            while(true){
                dataString = this->readLinePrompt(oss.str());
                newIngredient.setNameInredient(dataString);

                if(r->findDataL(newIngredient) != -1)
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
            
            r->insertSortedData(newIngredient);

            oss << this->divider("-");
            oss << "✅ ";
            oss << this->insertColorText("Ingrediente Añadido con Exito!", "green") << endl;
            oss << " 🥕 ¿Desea Añadir Más Ingredientes? (S/N): ";

            op = this->readChar(oss.str(), "S,N");

    } while(op != 'N');

}

void Menu::deleteIngredients(List<Ingredient, Configure::maximunIngredientSize>* r, const string& recipeName){
    if(r->isEmpty()){
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
            if(!r->isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Ingredientes Actual para " + recipeName, "magenta"));
                oss << r->toString() << endl;
                oss << this->divider();
            }
            oss << this->centerText("Ingrese 'fin' para regresar");
            oss << this->insertColorText("    Ingrese el Nombre del Ingrediente a Eliminar: ", "cyan") << endl;
            dataString = this->readLinePrompt(oss.str());

            searchedIngredient.setNameInredient(dataString);    
            dataInt = r->findDataL(searchedIngredient);

            if(dataInt == -1){
                oss << "Ingrediente " << this->insertColorText("No Encontrado", "red") << endl;
            }

            else{
                oss << this->insertColorText("¿Esta Seguro que Desea Eliminar Este Ingrediente? (S/N): ", "yellow");
                op = this->readChar(oss.str(), "S,N");
                if(op == 'S'){
                    r->deleteData(dataInt);
                    oss << this->centerText(this->insertColorText("!Ingrediente Eliminado Con Exito!", "green"));
                    this->modify = true;
                }
                else
                    oss << this->centerText(this->insertColorText("Eliminacion Cancelada", "red"));
            }

            oss << " ❌ ¿Desea Eliminar Más Ingredientes? (S/N): ";

            op = this->readChar(oss.str(), "S,N");

    } while(op != 'N' && !r->isEmpty());
 
}

void Menu::modifyIngredient(List<Ingredient, Configure::maximunIngredientSize>* r, const std::string& recipeName){
        if(r->isEmpty()){
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
                oss << r->toString() << endl;
                oss << this->divider();

                oss << this->insertColorText("    Ingrese el nombre del Ingrediente a Modificar: ", "cyan");
                
                dataString = this->readLinePrompt(oss.str());
                searched.setNameInredient(dataString);
                dataInt = r->findDataL(searched);

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
                            r->retrieve(dataInt)->setNameInredient(dataString);
                            break;
                        case 'B':
                            oss << this->insertColorText("    Ingrese la Nueva Cantidad del Ingrediente: ", "cyan");
                            dataFloat = this->readFloat(oss.str(),0,99999);
                            r->retrieve(dataInt)->setAmount(dataFloat);                        
                            break;
                        case 'C':
                            oss << this->insertColorText("    Ingrese la Nueva Unidad de Medida Ingrediente: ", "cyan");
                            dataString = this->readLinePrompt(oss.str());
                            r->retrieve(dataInt)->setUnit(dataString);                    
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

void Menu::menuPreocedure(List<StringWrapper, Configure::maximunIngredientSize>* r, const std::string& recipeName){
    if(r->isEmpty()){
        this->errorMessage("No hay Pasos Registrados\nRegresando...");
        return;
    }
    ostringstream oss;
    char op;

    do{
        oss.str("");
        oss.clear();
        
        oss << this->windowHeader("RECETARIO DIGITAL - MODIFICAR LISTA DE PASOS");
        oss << r->toString(true);
        oss << this->divider("-");
        oss << this->insertColorText("    [A] ", "cyan") << "Agregar Pasos" << endl;
        oss << this->insertColorText("    [B] ", "cyan") << "Eliminar Pasos" << endl;
        oss << this->insertColorText("    [C] ", "cyan") << "Modificar Pasos" << endl;
        oss << this->insertColorText("    [R] ", "cyan") << "Regresar" << endl; 
        oss << "Ingrese una Opción: ";
        op = this->readChar(oss.str(), "A,B,C,R");
        switch(op){
            case 'A':
                this->addProcedure(r, recipeName);
                break;
            case 'B':
                this->deleteProcedure(r, recipeName);
                break;
            case 'C':
                this->modifyProcedure(r, recipeName);
                break;
        }
    } while(op != 'R');
}


void Menu::addProcedure(List<StringWrapper, Configure::maximunIngredientSize>* r, const std::string& recipeName){
    ostringstream oss;
    char op;
    string dataString;
    StringWrapper newStep;
    try{
    do{
            oss.str("");
            oss.clear();

            oss << this->windowHeader("🥑 RECETARIO DIGITAL - AÑADIENDO PASOS");
            if(!r->isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Pasos Actual para " + recipeName, "magenta"));
                oss << r->toString(true) << endl;
                oss << this->divider();
            }
            oss << this->insertColorText("    Ingrese '/r' para Cancelar", "red") << endl;
            oss << this->insertColorText("    Ingrese el Nuevo Paso Para La Receta: ", "cyan");
            newStep = this->readLinePrompt(oss.str());


            oss << newStep << endl;
            
            r->insertElement(newStep, r->getLastPosition()+1);

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

void Menu::deleteProcedure(List<StringWrapper, Configure::maximunIngredientSize>* r, const std::string& recipeName){
    if(r->isEmpty()){
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
            if(!r->isEmpty()){
                oss << this->centerText("👍" + this->insertColorText("Lista de Pasos Actual para " + recipeName, "magenta"));
                oss << r->toString(true) << endl;
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
                
                    r->retrieve(dataInt);
                    oss << dataInt << endl;
                    oss << this->insertColorText("¿Esta Seguro que Desea Eliminar Este Ingrediente? (S/N): ", "yellow");
                    op = this->readChar(oss.str(), "S,N");
                    oss << op << endl;
                    if(op == 'S'){
                        r->deleteData(dataInt);
                        oss << this->centerText(this->insertColorText("!Paso Eliminado Con Exito!", "green"));
                        this->modify = true;
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
        
    } while(op != 'N' && !r->isEmpty());

    this->errorMessage("Ya No Hay Pasos Registrados.\nRegresando...");
}

void Menu::modifyProcedure(List<StringWrapper, Configure::maximunIngredientSize>* r, const string& recipeName){
        if(r->isEmpty()){
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
                oss << r->toString(true) << endl;
                oss << this->divider();
                oss << this->insertColorText("    Ingrese '/r' Para Cancelar", "red") << endl;
                oss << this->insertColorText("    Ingrese el Índice del Paso a Modificar: ", "cyan");
                
                dataInt = this->readInteger(oss.str(), 0, 999999);

                try{
                    searched = r->retrieve(dataInt - 1);
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


void Menu::enterToContinue() {
    cout << "+----------------------------------+" << endl;
    cout << "|         Presiones [ENTER]        |" << endl;
    cout << "|           Para Continuar         |" << endl;
    cout << "+----------------------------------+" << endl;
    cin.ignore();
    cin.get();
}

std::string Menu::categoryToString(const Category& category) const{
    switch(category){
        case DESAYUNO: return "desayuno";
        case COMIDA: return "comida";
        case CENA: return "cena";
        case NAVIDEÑO: return "navideño";
    }
    return "";
}

void Menu::errorMessage(const std::string& prompt, const int& windowWidth){
    this->cleanScreen();
    auto printBorder = [&]() {
        std::cout << "+";
        for (int i = 0; i < windowWidth; ++i) std::cout << "-";
        std::cout << "+\n";
    };

    auto printCenteredLine = [&](const std::string& prompt = "") {
        int broad = static_cast<int>(prompt.size());
        int totalSpaces = windowWidth - broad;
        int leftSpaces = totalSpaces / 2;
        int rightSpaces = totalSpaces - leftSpaces;

        std::cout << "|";
        for (int i = 0; i < leftSpaces; ++i) std::cout << " ";
        std::cout << prompt;
        for (int i = 0; i < rightSpaces; ++i) std::cout << " ";
        std::cout << "|\n";
    };

    // --- Imprimir recuadro ---
    printBorder();
    printCenteredLine("[ERROR]");

    stringstream ss(prompt);
    string line;

    while (getline(ss, line, '\n')) 
        printCenteredLine(line);

    printBorder();  
    system("PAUSE");
}

bool Menu::handleOption(const string& prompt) {
    string validOptions("A,B,C,D,E,F,G,H,I,S");
    char op;

    op = this->readChar(prompt, validOptions);

    switch(op){
        case 'A':
            this->addRecipe();
            return true;
            break;
        case 'B':
            this->deleteRecipe();
            return true;
            break;
        case 'C':
            this->editRecipe();
            return true;
            break;
        case 'D':
            this->searchMenu();
            return true;
            break;
        case 'E':
            this->showRecipes();
            return true;
            break;
        case 'F':
            this->sortRecipes();
            return true;
            break;
        case 'G':
            this->saveToDisk();
            return true;
            break;
        case 'H':
            this->readFromDisk();
            return true;
            break;
        case 'I':
            this->exportRecipe();
            return true;
            break;
        case 'S':
            this->exitMenu();
            return false;
            break;
    }
}

string Menu::windowHeader(const string& prompt, const int& widthBorder, const string& c) const {
    ostringstream oss;
    int spaces((widthBorder - prompt.size()) / 2);

    oss << this->divider(c, widthBorder);
    oss << setw(spaces) << "" << prompt << endl;

    oss << this->divider(c, widthBorder);

  return oss.str();
}

std::string Menu::divider(const std::string& character, const int& size) const {
    std::string line;
    for (int i = 0; i < size; ++i) {
        line += character;
    }
    line += '\n';
    return line;
}

string Menu::insertColorText(std::string prompt, std::string color) {

    //Mapa o Diccionario para los colores
    std::unordered_map<string, string> colorMap = {
        {"red", "\033[31m"},
        {"green", "\033[32m"},
        {"yellow", "\033[33m"},
        {"blue", "\033[34m"},
        {"cyan", "\033[36m"},
        {"magenta", "\033[35m"},
    };

    auto it = colorMap.find(color);
    if(it != colorMap.end()){
        prompt.insert(0,it->second);
        prompt += "\033[37m";
    }

    return prompt;
}

std::string Menu::centerText(string prompt, const int& windowWidth){
        if(prompt.empty())
            return "";

        string result;
        int broad = prompt.size();
        int totalSpaces = windowWidth - broad;
        int leftSpaces = totalSpaces / 2;
        int rightSpaces = totalSpaces - leftSpaces;

        for (int i = 0; i < leftSpaces; ++i) result += " ";
        result += prompt;
        for (int i = 0; i < rightSpaces; ++i) result += " ";
        result += '\n';
    return result;
}

void Menu::cleanScreen() {
    system("CLS");
}


void Menu::showStartupAnimation(int duration_ms,
                                bool showProgressBar,
                                const std::string& alumno,
                                const std::string& profesor,
                                const std::string& materia,
                                const std::string& fecha) const
{
    // ASCII logo (personalizable)
    const char* logo[] = {
        R"(                ____  _____ ____ _____ _____  _    ____  ___ ___                )",
        R"(               |  _ \| ____/ ___| ____|_   _|/ \  |  _ \|_ _/ _ \               )",
        R"(    _____ _____| |_) |  _|| |   |  _|   | | / _ \ | |_) || | | | |_____ _____   )",
        R"(   |_____|_____|  _ <| |__| |___| |___  | |/ ___ \|  _ < | | |_| |_____|_____|  )",
        R"(               |_| \_\_____\____|_____| |_/_/   \_\_| \_\___\___/               )"
    };
    const int logoLines = sizeof(logo) / sizeof(logo[0]);

    // Box configuration
    const int boxWidth = 90;        // ancho total del recuadro
    const int innerWidth = boxWidth - 4; // espacio interior para texto
    const int topMarginLines = 1;

    auto printBoxLineCentered = [&](const std::string& text){
        int txtLen = static_cast<int>(text.size());
        int padding = std::max(0, innerWidth - txtLen);
        int leftPad = padding / 2;
        int rightPad = padding - leftPad;
        std::cout << "| " << std::string(leftPad, ' ') << text << std::string(rightPad, ' ') << " |\n";
    };

    // Helper to print a labeled field with an underline area (form)
    auto printField = [&](const std::string& label, const std::string& value){
        std::string lbl = label + ": ";
        int spaceForValue = innerWidth - static_cast<int>(lbl.size());
        std::string display;
        if (!value.empty()) {
            // if value fits, print it; otherwise truncate with ellipsis
            if ((int)value.size() <= spaceForValue) display = value + std::string(spaceForValue - (int)value.size(), ' ');
            else display = value.substr(0, spaceForValue-3) + "...";
        } else {
            // underline placeholder
            display = std::string(spaceForValue, '_');
        }
        std::cout << "| " << lbl << display << " |\n";
    };

    // Clear and draw top margin
    system("CLS");
    for (int i = 0; i < topMarginLines; ++i) std::cout << "\n";

    // Top border
    std::cout << "+" << std::string(boxWidth - 2, '-') << "+\n";

    // Empty spacer row
    std::cout << "| " << std::string(innerWidth, ' ') << " |\n";

    // Logo centered (reserve a few lines)
    for (int i = 0; i < logoLines; ++i) {
        printBoxLineCentered(logo[i]);
    }

    // Empty spacer
    std::cout << "| " << std::string(innerWidth, ' ') << " |\n";

    // Title centered
    printBoxLineCentered("RECETARIO DIGITAL");

    // Subtitle
    printBoxLineCentered("Inicializando...");

    // Empty spacer
    std::cout << "| " << std::string(innerWidth, ' ') << " |\n";

    // Metadata fields (Alumno, Profesor, Materia, Fecha)
    printField("Alumno", alumno);
    printField("Profesor", profesor);
    printField("Materia", materia);
    printField("Fecha", fecha);

    // Empty spacer at bottom of box
    std::cout << "| " << std::string(innerWidth, ' ') << " |\n";

    // Bottom border
    std::cout << "+" << std::string(boxWidth - 2, '-') << "+\n\n";

    // Spinner + optional progress bar below the box
    const std::string spinner = "|/-\\";
    const int spinnerCount = static_cast<int>(spinner.size());
    const int spinnerIntervalMs = 100;
    int total = std::max(1, duration_ms);
    int steps = std::max(1, total / spinnerIntervalMs);

    for (int step = 0; step < steps; ++step) {
        char s = spinner[step % spinnerCount];
        std::cout << "\r  [" << s << "] ";
        if (showProgressBar) {
            const int barWidth = 40;
            double frac = static_cast<double>(step) / static_cast<double>(steps);
            int pos = static_cast<int>(barWidth * frac);
            std::cout << "[";
            for (int i = 0; i < barWidth; ++i) {
                if (i < pos) std::cout << "=";
                else if (i == pos) std::cout << ">";
                else std::cout << " ";
            }
            std::cout << "] ";
            int percent = static_cast<int>(frac * 100.0);
            if (percent > 100) percent = 100;
            std::cout << std::setw(3) << percent << "%";
        } else {
            std::cout << "Cargando...";
        }
        std::cout << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(spinnerIntervalMs));
    }

    // Finish: force 100% display
    if (showProgressBar) {
        const int barWidth = 40;
        std::cout << "\r  [*] [";
        for (int i = 0; i < barWidth; ++i) std::cout << "=";
        std::cout << "] 100%\n";
    } else {
        std::cout << "\r  [*] Listo.\n";
    }

    std::cout << std::flush;

    // Short pause so the user sees final state
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Clear screen before entering menu (optional)
    system("CLS");
}


void Menu::insertSortedDataByCategory(const Recipe& newData) {
    if(this->sortedBy == "id")
        this->recipeBook.insertSortedData(newData);
    else if(this->sortedBy == "recipeName")
        this->recipeBook.insertSortedData(newData, Recipe::compareByName);
    else if(this->sortedBy == "preparationTime")
        this->recipeBook.insertSortedData(newData, Recipe::compareByPreparationTime);
    else if(this->sortedBy == "category")
        this->recipeBook.insertSortedData(newData, Recipe::compareByCategory);
    else if(this->sortedBy == "author")
        this->recipeBook.insertSortedData(newData, Recipe::compareByAuthor);
    else if(this->sortedBy == "creationDate")
        this->recipeBook.insertSortedData(newData, Recipe::compareByCreationDate);
    else
        throw MenuExceptions::InvalidInsertCategory();
}

Recipe* Menu::searcher(const string& prompt, int& index) {
    ostringstream oss;
    char op;
    int dataInt;
    string dataString;
    Name dataName;
    Date dataDate;
    Category dataCategory;

    string colorOpts("cyan");
    Recipe searchedRecipe;
    

    oss << prompt << endl;
    oss << this->insertColorText("Mediante Que Parámetro Quiere Buscar Su Receta: ", "green") << endl;
    oss << this->insertColorText("    [A] ", colorOpts) << "🔢 ID" << endl;
    oss << this->insertColorText("    [B] ", colorOpts) << "🍲 Nombre de la Receta" << endl;
    oss << this->insertColorText("    [C] ", colorOpts) << "👨‍🍳 Autor" << endl;
    oss << this->insertColorText("    [D] ", colorOpts) << "🎃 Categoría (Primera Coincidencia)" << endl; 
    oss << this->insertColorText("    [R] ", colorOpts) << "↩️ Regresar" << endl;
    oss << this->insertColorText("Ingrese una Opcion: ", "cyan");
    
    op = this->readChar(oss.str(), "A,B,C,D,R");
    oss << op << endl;

    switch (op){
    case 'A':
        oss << "\n" << this->insertColorText("    Ingrese el ID a Buscar: ", "cyan");
        dataInt = this->readInteger(oss.str(),0,99999);
        searchedRecipe.setId(dataInt);
        index = this->recipeBook.findDataL(searchedRecipe);
        break;
    case 'B':
        oss << "\n" << this->insertColorText("    Ingrese el Nombre de la Receta a Buscar: ", "cyan");
        dataString = this->readLinePrompt(oss.str());
        searchedRecipe.setRecipeName(dataString);
        index = this->recipeBook.findDataL(searchedRecipe, Recipe::compareByName);
        break;
    case 'C':
        dataName = this->readName(oss.str(), this->insertColorText("    Ingrese el Nombre del Chef: ", "cyan"), this->insertColorText("    Inhrese el Apellido del Chef: ", "cyan"));
        searchedRecipe.setAuthor(dataName);
        index = this->recipeBook.findDataL(searchedRecipe, Recipe::compareByAuthor);
        break;
    case 'D':
        oss << this->insertColorText("    Ingrese la Categoría : ", "cyan");
        oss << "    Categoría: " << this->insertColorText("[1] ", "magenta") << this->insertColorText("Desayuno", "green") << this->insertColorText("[2] ", "magenta") << this->insertColorText("Comida", "green") << this->insertColorText("[3] ", "magenta") << this->insertColorText("Cena", "green") << this->insertColorText("[4] ", "magenta") << this->insertColorText("Navideño", "green") << ": "; 

        dataCategory = this->readCategory(oss.str());
        searchedRecipe.setCategory(dataCategory);
        index = this->recipeBook.findDataL(searchedRecipe, Recipe::compareByCategory);
        break;
    case 'R':
        return nullptr;
    }

    return index == -1 ? nullptr : this->recipeBook.retrieve(index);

}

void Menu::addRecipe() {
    ostringstream oss;
    string dataString, dataString2;
    Name dataName;
    int dataInt, dataInt2;
    Category dataCategory;
    char op;
    
    do{
        Recipe newRecipe;

        oss.str("");
        oss.clear();
        
        this->cleanScreen();
        
        oss << this->windowHeader("🌮 RECETARIO DIGITAL - AÑADIR RECETA");
        oss << this->centerText("Vamos a Agregar Una Nueva Receta");
        oss << this->centerText("Ingrese '/r' en Cualquier Momento para Cancelar");
        oss << this->divider("-");

        try{
            oss << this->insertColorText("    Ingrese el ID Numérico del Platillo: ", "cyan");
            while(true){
                dataInt = this->readInteger(oss.str(), 0, 9999999);
                newRecipe.setId(dataInt);
                dataInt2 = this->recipeBook.findDataL(newRecipe);
                if(dataInt2 != -1){
                    dataString = this->recipeBook.retrieve(dataInt2)->toString();
                    this->errorMessage("El ID ya esta registrado: \n" + dataString + "\nIntentelo Nuevamente");
                }
                else
                    break;
        }
        oss << dataInt << endl;

            oss << this->insertColorText("    Ingrese el Nombre del Platillo: ", "cyan");
            dataString = this->readLinePrompt(oss.str());
            oss << dataString << endl;
            newRecipe.setRecipeName(dataString);

            dataString = this->insertColorText("    Ingrese el Nombre del Chef: ", "cyan");
            dataString2 = this->insertColorText("    Ingrese el Apellido del Chef: ", "cyan");

            dataName = this->readName(oss.str(), dataString, dataString2);
            oss << dataString << dataName.getFirst() << endl;
            oss << dataString2 << dataName.getLast() << endl;
            newRecipe.setAuthor(dataName);

            oss << "    Categoría: " << this->insertColorText("[1] ", "magenta") << this->insertColorText("Desayuno", "green") << this->insertColorText("[2] ", "magenta") << this->insertColorText("Comida", "green") << this->insertColorText("[3] ", "magenta") << this->insertColorText("Cena", "green") << this->insertColorText("[4] ", "magenta") << this->insertColorText("Navideño", "green") << ": "; 
            dataCategory = this->readCategory(oss.str());
            oss << this->insertColorText("    Categoria Seleccionada: ", "cyan") << this->categoryToString(dataCategory) << endl;
            newRecipe.setCategory(dataCategory);
            
            oss << this->insertColorText("    Ingrese el Tiempo de Preparacion en Minutos: ", "cyan");
            dataInt = this->readInteger(oss.str(), 1, 99999);
            oss << dataInt << endl;
            newRecipe.setPreparationTime(dataInt);

            //Añadir los Ingredientes que el usuario Desee
            this->addIngredients(&newRecipe.getIngredientList(), newRecipe.getRecipeName());
            oss << this->insertColorText("    Inserte el Procedimiento Paso a Paso", "cyan") << endl;
            oss << "        Ingrese '" << this->insertColorText("fin", "red") << "' para terminar." << endl;
            dataInt = 1;
            while(true){
                dataString = this->readLinePrompt(oss.str());
                if(dataString == "fin")
                    break;
                oss <<"    " << dataInt <<". " << dataString << endl;
                newRecipe.addStepToProcedure(dataString);
                dataInt++;
            }

            newRecipe.setCreationDate(Date());

            this->insertSortedDataByCategory(newRecipe);
            this->modify = true;

        } catch(const InputExceptions::OperationCanceledException& ex){
            this->errorMessage("Operación Canelada\nRegresando...");
            return;
        }
        oss << this->centerText(this->insertColorText(" ✅ !Receta Agrega Con Éxito¡", "green"));
        oss << this->insertColorText(" ❓ ¿Desea Ingresar Una Nueva Receta? (S/N): ", "yellow");
        op = this->readChar(oss.str(), "S,N");
        
    }while(op != 'N');
}

void Menu::deleteRecipe() {
    if(this->recipeBook.isEmpty()){
        this->errorMessage("No Hay Recetas Registradas\nIngrese Recetas Antes");
        return;
    }
    
    ostringstream oss;
    char op, ver;
    int index = 23;
    Recipe* objetive = nullptr;
    this->cleanScreen();
    
    
        do{
        oss.str("");
        oss.clear();
        oss << this->windowHeader("RECETARIO DIGITAL - ELIMINAR UNA RECETA");
        objetive = this->searcher(oss.str(), index);

        if(objetive == nullptr){
            oss << "Receta " << this->insertColorText("No Encontrada", "red") << endl;
            oss << this->insertColorText("¿Desea Intentar Otra Búsqueda? (S/N): ", "yellos");
            op = this->readChar(oss.str(), "S,N");
        }
        else{
            oss << this->insertColorText("¡Receta Encontrada!", "green") << endl;
            oss << objetive->toString() << endl;
            oss << "¿Esta Seguro Que Desea Eliminarla? (S/N): ";
            ver = this->readChar(oss.str(), "S,N");
            oss << ver << endl;

            if(ver == 'S'){
                this->recipeBook.deleteData(index);
                oss << this->centerText(this->insertColorText("¡Receta Eliminada Con Exito!", "green")) << endl;
                this->modify = true;
            }
            else{
                oss << this->insertColorText("    Eliminación Cancelada.", "cyan") << endl;
            }
            
            oss << "¿Realizar Otra Eliminación? (S/N): ";
            op = this->readChar(oss.str(), "S,N");
        }

    }while(op != 'N' && !this->recipeBook.isEmpty());

    this->errorMessage("Ya No Hay Recetas Registradas\nVuelva a Ingresar Más Recetas");
}

void Menu::editRecipe() {
    if(this->recipeBook.isEmpty()){
        this->errorMessage("No Hay Recetar Registradas.\nRegresando...");
        return;
    }

    char op, repeater;
    int dataInt, dataInt2;
    string dataString;
    Name dataName;
    Category dataCategory;
    Date dataDate;
    ostringstream oss;
    int index;
    Recipe* objetive;
    Recipe searched;
    
    do{
        oss.str("");
        oss.clear();
        
        this->cleanScreen();
        oss << this->windowHeader("✍️ RECETARIO DIGITA - EDITAR RECETA");
        objetive = this->searcher(oss.str(), index);

        if(objetive != nullptr){
            oss << objetive->toString() << endl;
            oss << this->centerText("Seleccione el Apartado a Modificar: ") << endl;
            oss << this->divider("-");
            
            oss << this->insertColorText("[A] ", "cyan") << "Id" << endl;
            oss << this->insertColorText("[B] ", "cyan") << "Nombre de la Receta" << endl;
            oss << this->insertColorText("[C] ", "cyan") << "Autor" << endl;
            oss << this->insertColorText("[D] ", "cyan") << "Categoría" << endl;
            oss << this->insertColorText("[E] ", "cyan") << "Tiempo de Preparación" << endl;
            oss << this->insertColorText("[F] ", "cyan") << "Procedimiento" << endl;
            oss << this->insertColorText("[G] ", "cyan") << "Lista de Ingredientes" << endl;
            //oss << this->insertColorText("[H] ", "cyan") << "Fecha de Creación" << endl;
            oss << this->insertColorText("[R] ", "cyan") << "Regresar" << endl;
            oss << this->divider("-");
            oss << "Seleccione una opción: ";
            op = this->readChar(oss.str(), "A,B,C,D,E,F,G,H,R");
            oss << op << endl;

            try{
                switch(op){
                    case 'A':
                        oss << this->insertColorText("    Ingrese el nuevo ID: ", "yellow");
                        dataInt = this->readInteger(oss.str(),0,99999);
                        searched.setId(dataInt);
                        dataInt2 = this->recipeBook.findDataL(searched);
                        if(dataInt2 != -1)
                            this->errorMessage("ID ya registrado: \n" + this->recipeBook.retrieve(dataInt2)->toString());
                        else{
                            objetive->setId(dataInt);
                            oss << dataInt << endl;
                        }
                        break;
                    case 'B':
                        oss << this->insertColorText("    Ingrese el Nuevo Nombre de la Receta: ", "yellow");
                        dataString = this->readLinePrompt(oss.str());
                        objetive->setRecipeName(dataString);
                        oss << dataString << endl;
                        break;
                    case 'C':
                        dataName = this->readName(oss.str(), this->insertColorText("    Inserte el Nuevo Nombre del Chef: ", "yellow"), this->insertColorText("    Ingrese el Nuevo Apellido del Chef: ", "yellow"));
                        oss << this->insertColorText("    Ingrese el Nuevo Nombre del Chef: ", "yellow") << dataName.getFirst() << endl;
                        oss << this->insertColorText("    Ingrese el Nuevo Apellido del Chef: ", "yellow") << dataName.getLast() << endl;
                        objetive->setAuthor(dataName);
                        break;
                    case 'D':
                        oss << this->insertColorText("    Ingrese la Nueva Categoría de la Receta: ", "yellow");
                        dataCategory = this->readCategory(oss.str());
                        oss << this->categoryToString(dataCategory) << endl;
                        objetive->setCategory(dataCategory);
                        break;
                    case 'E':
                        oss << this->insertColorText("    Ingrese el Nuevo Tiempo de Preparación en Minutos: ", "yellow");
                        dataInt = this->readInteger(oss.str(), 0, 999999);
                        oss << dataInt << endl;
                        objetive->setPreparationTime(dataInt);
                        break;
                    case 'F':
                       this->menuPreocedure(&objetive->getProcedureList(), objetive->getRecipeName());
                        break;
                    case 'G':
                        this->menuIngredints(&objetive->getIngredientList(), objetive->getRecipeName());
                        break;
                    case 'H':
                        break;
                    case 'R':
                        return;
                        break;                                                                                            
                }
            } catch(const InputExceptions::OperationCanceledException& ex){
                this->errorMessage("Operación Cancelada\nRegresando...");
                return;
            }
            oss << this->centerText(this->insertColorText("Modificación Realizada con Exito", "green"));
        }

        else
            this->errorMessage("Receta No Encontrada\nRegresando...");

        oss << "¿Desea Realizar Otra Modificación? (S/N): ";
        repeater = this->readChar(oss.str(), "S,N");
    } while(repeater != 'N');
}

void Menu::showRecipes() {
    if(this->recipeBook.isEmpty()){
        this->errorMessage("No Hay Recetas Que Mostar\nRegresando...");
        return;
    }

    ostringstream oss;
    char op, repeater;
    Category dataCategory;
    Recipe comparative;

    do{

        oss.str("");
        oss.clear();
        oss << this->windowHeader(" 👀 RECETARIO DIGITAL - MOSTAR RECETAS");
        oss << this->centerText(this->insertColorText("Mostrar Todas las Recetas o Filtradas", "blue")) << endl;
        oss << this->divider("-");

        oss << this->insertColorText("    [A] ", "cyan") << "Mostrar Todas las Recetas" << endl;
        oss << this->insertColorText("    [B] ", "cyan") << "Filtrar Por Categoría" << endl;
        oss << this->insertColorText("    [R] ", "cyan") << "Regresar" << endl;
        oss << this->insertColorText("Seleccione Una Opción: ", "yellow");
        op = this->readChar(oss.str(), "A,B,R");

        oss << op << endl;
        try{
            switch(op){
                case 'A':
                    oss.str("");
                    oss.clear();
                    oss << this->windowHeader("TODAS LAS RECETAS");
                    oss << this->recipeBook.toString() << endl;
                    oss << this->divider();
                    break;

                case 'B':
                    oss << this->insertColorText("Ingrese /r para Cancelar", "red") << endl;
                    oss << this->insertColorText("    Seleccione una Categoría ", "yellow");
                    oss << "    Categoría: " << this->insertColorText("[1] ", "magenta") << this->insertColorText("Desayuno", "green") << this->insertColorText("[2] ", "magenta") << this->insertColorText("Comida", "green") << this->insertColorText("[3] ", "magenta") << this->insertColorText("Cena", "green") << this->insertColorText("[4] ", "magenta") << this->insertColorText("Navideño", "green") << ": "; 
                    dataCategory = this->readCategory(oss.str());
                    comparative.setCategory(dataCategory);

                    oss.str("");
                    oss.clear();

                    oss << this->windowHeader("TODAS RECETAS TIPO: " + this->categoryToString(dataCategory));
                    oss << this->recipeBook.toString(comparative, Recipe::compareByCategory);
                    oss << this->divider();
                    break;
                case 'R':
                    return;
                    break;
            }
        } catch(const InputExceptions::OperationCanceledException& ex){
            this->errorMessage("Operación Cancelada.\nRegresando...");
            return;
        }
        oss << "¿Desea Repetir el Menú? (S/N) ✔️: ";
        repeater = this->readChar(oss.str(), "S,N");
    } while(repeater != 'N');
}

void Menu::searchMenu() {
    if(this->recipeBook.isEmpty()){
        this->errorMessage("No hay Recetas Registradas.\nRegresando...");
        return;
    }    
    ostringstream oss;
    Recipe* searched;
    char op;
    int aux;
    
    do{
        oss.str("");
        oss.clear();
        oss << this->windowHeader(" 🔍 RECETARIO DIGITAL - BUSCAR RECETA");
        searched = this->searcher(oss.str(), aux);

        if(searched == nullptr)
            oss << this->centerText( "Receta " + this->insertColorText("No Encontrada", "red"));
        else
            oss << searched->toString();
        oss << this->insertColorText("¿Desea Buscar Otra Receta (S/N)?: ", "yellow");
        op = this->readChar(oss.str(), "S,N");
    } while(op != 'N');

}

void Menu::sortRecipes(){
    if(this->recipeBook.getLastPosition() + 1 < 2){
        this->errorMessage("No Hay Suficientes Recetas Registradas.\nNo Se Requiere Ordenamiento.");
        return;
    }
    ostringstream oss;
    Recipe categorySort;
    char op;
    string dataString;
    Name dataName;
    Date dateTime;

    oss << this->windowHeader(" 🗃️ RECETARIO DIGITA - ORDENAR RECETAS");
    oss << this->insertColorText("Seleccione Sobre Qué Categoría Quiere Ordenar Sus Recetas: ", "yellow") << endl;
    oss << this->divider();

    oss << this->insertColorText("    [A] ", "cyan") << "Ordenar por ID" << endl;
    oss << this->insertColorText("    [B] ", "cyan") << "Ordenar por Nombre de la Receta" << endl;
    oss << this->insertColorText("    [C] ", "cyan") << "Ordenar por Nombre del Autor" << endl;
    oss << this->insertColorText("    [D] ", "cyan") << "Ordenar por Categoría" << endl;
    oss << this->insertColorText("    [E] ", "cyan") << "Ordenar por Tiempo de Preparación" << endl;
    oss << this->insertColorText("    [F] ", "cyan") << "Ordenar por Por Fecha de Creación" << endl;
    oss << this->insertColorText("    [S] ", "cyan") << "Salir" << endl;
    oss << this->insertColorText("Seleccione una Opción: ", "yellow");

    op = this->readChar(oss.str(), "A,B,C,D,E,F,S");

    switch(op){
        case 'A':
            this->recipeBook.sortDataQuick();
            this->sortedBy = "id";
            break;
        case 'B':
            this->recipeBook.sortDataQuick(Recipe::compareByName);
            this->sortedBy = "recipeName";
            break;
        case 'C':
            this->recipeBook.sortDataQuick(Recipe::compareByAuthor);
            this->sortedBy = "author";        
            break;
        case 'D':
            this->recipeBook.sortDataQuick(Recipe::compareByCategory);
            this->sortedBy = "category";        
            break;
        case 'E':
            this->recipeBook.sortDataQuick(Recipe::compareByPreparationTime);
            this->sortedBy = "preparationTime";        
            break;
        case 'F':
            this->recipeBook.sortDataQuick(Recipe::compareByCreationDate);
            this->sortedBy = "creationDate";        
            break;
        case 'S':
            return;
            break;
    }
    oss << this->centerText(this->insertColorText("¡Datos Ordenados Con Éxito!", "green"));
    this->cleanScreen();
    cout << oss.str();
    system("PAUSE");
}

void Menu::saveToDisk() {
    if(this->recipeBook.isEmpty()){
        this->errorMessage("No Hay Recetas Que Guardar\nRegresando...");
        return;
    }
    string dataString;
    ostringstream oss;

    oss << this->windowHeader(" 💾 RECETARIO DIGITAL - GUARDAR RECETAS EN EL DISCO ");
    oss << this->centerText(this->insertColorText("Ingrese '/r' para Cancelar la Operación", "yellow")) << endl;
    oss << this->divider("-");
    oss << this->insertColorText("Ingrese el Nombre con el Cual Quiere Guardar al Disco (Se Guardará en Formato .Json): ", "yellow");
    
    try{
        dataString = this->readLinePrompt(oss.str());

        ofstream dataFile(dataString + ".json");

        if(dataFile.is_open()){
            dataFile << this->recipeBook.toJson().dump(4);
            oss << dataString + ".json" << endl;
            oss << this->centerText(this->insertColorText(" ✅ ¡Datos Guardados Con Éxito!", "green"));
            dataFile.close();
        }
        else
            oss << this->centerText(this->insertColorText(" ❌ Ha Ocurrido Un Error Al Crear el Archivo.", "red"));

    } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Operación Cancelada\nRegresando");
        return;
    }

    this->cleanScreen();
    oss << this->insertColorText("Regresando...", "magenta");
    cout << oss.str() << endl;
    system("PAUSE");

}

void Menu::readFromDisk() {
    ostringstream oss;
    string dataString;

    oss << this->windowHeader(" 💽 RECETARIO DIGITAL - LEER RECETAS DEL ALMACENAMIENTO");
    oss << this->insertColorText("ADVERTENCIA: Si se leen datos con registros en la aplicación\n estos serán sobrescritos", "red") << endl;
    oss << this->centerText(this->insertColorText("Ingrese '/r' para cancelar", "cyan")) << endl;
    oss << this->divider("-");
    oss << this->insertColorText("Ingrese el Nombre de la Base de Datos .json (sin la extensión):", "yellow");
    
    try{
        dataString = this->readLinePrompt(oss.str());
        ifstream dataFile(dataString + ".json");

        if(dataFile.is_open()){
            nlohmann::json js;
            dataFile >> js;
            this->recipeBook.fromJson(js.at("data"));
            dataFile.close();
            oss << dataString << ".json" << endl;
            oss << this->centerText(this->insertColorText(" ✅ ¡Datos Cargados Con Éxito!", "green")) << endl;
        
            //Recuperar el Tipo de Orden que Tenía
            if(this->recipeBook.isSorted())
                this->sortedBy = "id";
            else if(this->recipeBook.isSorted(Recipe::compareByName))
                this->sortedBy = "recipeName";
            else if(this->recipeBook.isSorted(Recipe::compareByAuthor))
                this->sortedBy = "author";
            else if(this->recipeBook.isSorted(Recipe::compareByCategory))
                this->sortedBy = "category";
            else if(this->recipeBook.isSorted(Recipe::compareByCreationDate))
                this->sortedBy = "creationDate";
        }


    } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Operación Cancelada\nRegresando...");
        return;
    }

    this->cleanScreen();
    oss << this->insertColorText("Regresando...","magenta");
    cout << oss.str() << endl;
    system("PAUSE");
}

void Menu::exportRecipe(){
    if(this->recipeBook.isEmpty()){
        this->errorMessage("No Hay Recetas Que Exportar\n");
        return;
    }

    ostringstream oss;
    Recipe* r;
    int index;
    string dataString;
    char op;

    do{
        oss.str("");
        oss.clear();
        oss << this->windowHeader("RECETARIO DIGITAL - EXPORTAR UNA RECETA.");
        r = this->searcher(oss.str(), index);

        if(r == nullptr){
            oss << this->centerText(this->insertColorText("Receta No Encontrada", "red")) << endl;
        }
        else{
            oss << r->toString() << endl;
            oss << this->divider("-");
            oss << this->insertColorText("Ingrese el Nombre del Archivo Destino (con extensión): ", "cyan");
            dataString = this->readLinePrompt(oss.str());
            oss << dataString << endl;
            ofstream os(dataString);
            if(os.is_open()){
                os << this->clearColor(r->toString());
                os.close();
                oss << this->centerText(this->insertColorText("!Exportación Realizada con Éxito!", "green"))  << endl;
                }
            else{
                this->insertColorText("El Archivo no se Puedo Crear", "red");
            }
        }

        oss << this->insertColorText("¿Desea Realizar Otra Exportación? (S/N): ", "yellow");
        op = this->readChar(oss.str(), "S,N");

    } while(op != 'N');
}

void Menu::exitMenu(){
    ostringstream oss;
    char op;
    if(this->modify){
        oss << this->windowHeader("👋 RECETARIO DIGITAL - SALIENDO DEL RECETARIO");
        oss << "Hubo Cambios en las Recetas Aún no Guardados" << endl;
        oss << this->insertColorText("    ¿Desea Guardar los Cambios Antes de Salir? (S/N): ", "cyan");
        op = this->readChar(oss.str(), "S,N");
        oss << op << endl;
        
        if(op == 'S')
            this->saveToDisk();
    }

    oss.str("");
    oss.clear();
    oss << this->divider();
    oss << this->centerText(this->insertColorText("Saliendo del Programa.", "cyan")) << endl;
    oss << this->centerText(this->insertColorText("Que Tenga un Lindo Día :D", "cyan")) << endl;
    oss << this->divider();

    this->cleanScreen();
    cout << oss.str();
    system("PAUSE");
}

void Menu::mainMenu() {
    bool repeater;
    ostringstream oss;
    string colorOpts = "cyan";
    
    do{
        oss.str("");
        oss.clear();
        this->cleanScreen();
        oss << this->windowHeader("🍽️ MENU PRINCIPAL - GESTIÓN DE RECETAS");
        
        oss << "    " << this->insertColorText("[A]", colorOpts) << " 🍜 Agregar Nueva Receta" << endl;
        oss << "    " << this->insertColorText("[B]", colorOpts) << " ❌ Eliminar Una Receta" << endl;
        oss << "    " << this->insertColorText("[C]", colorOpts) << " 🖋️ Modificar Una Receta" << endl;
        oss << "    " << this->insertColorText("[D]", colorOpts) << " 🔍 Buscar Una Receta" << endl;
        oss << "    " << this->insertColorText("[E]", colorOpts) << " 📋 Mostrar Recetas" << endl;
        oss << "    " << this->insertColorText("[F]", colorOpts) << " 🗒️ Ordenar El Catalogo de Recetas" << endl;
        oss << "    " << this->insertColorText("[G]", colorOpts) << " 💾 Guardar al Disco" << endl; 
        oss << "    " << this->insertColorText("[H]", colorOpts) << " 📩 Cargar Recetas del Disco" << endl;
        oss << "    " << this->insertColorText("[I]", colorOpts) << " 📄 Exportar Una Receta" << endl;
        oss << "    " << this->insertColorText("[S]", colorOpts) << " 👋🏻 Salir del Programa" << endl;

        oss << this->divider() << endl;

        oss << "Selecione una Opcion [A...S]: ";        
        repeater = this->handleOption(oss.str());

    } while(repeater);
}

Menu::Menu() : recipeBook(* new List<Recipe>), sortedBy("id"), modify(false) {
    this->showStartupAnimation();
    this->mainMenu();
}

Menu::Menu(const Menu& other) : recipeBook(other.recipeBook) {
    this->showStartupAnimation();
    this->mainMenu();
}

Menu::Menu(List<Recipe>& l, const std::string& s, const bool& m) : recipeBook(l), sortedBy(s), modify(m) {
    this->showStartupAnimation();
    this->mainMenu();
}
