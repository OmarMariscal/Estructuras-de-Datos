#include "menu.hpp"

using namespace std;

bool Menu::handleOption(const std::string& promt) {
  char option;

  this->cleanScreen();

  option = this->readChar(promt, "T,R,E,S");

  switch (option) {
    case 'T':
      this->makeTranformation();
      break;
    case 'R':
      this->showRecord();
      break;
    case 'E':
      this->deleteRecords();
      break;
    case 'S':
      this->exitScreen();
      return false;
      break;
  }  // switch

  return true;
}

void Menu::makeTranformation() {
  ostringstream oss;
  char repeater;
  string infixNotation;
  Queue<char> queueNotation;

  do{ //Bucle para repetir transformaciones
    // Bucle perpetuo hasta que se ingresa una expresión válida
    while (true) {
      try {
        system("CLS");
        oss.str("");
        oss.clear();
        oss << this->windowHeader("Transformar de Notacion Infija a PostFija");
        oss << this->centerText("Para Cancelar, Ingrese '/r'");
        oss << this->divider("-");


        oss << this->insertColorText("    Ingrese la operacion en notacion infija: ", "cyan");
        infixNotation = this->readLinePrompt(oss.str());
        oss << infixNotation << endl;
        
        queueNotation = this->transformer.stringToQueue(infixNotation);

        this->transformer.setInflixQueue(queueNotation);
        break;  // Si no hay excepción salimos del bucle.
      } catch (const NotationTransformerExceptions::InvalidExpresion&
                  ex) {  // Manejo de la Excepción Personalizada
        this->errorMessage("La expresion no es valida.\nRecuerde que no se pueden tener dos operadores juntos (3++5)\nParentesis que no se cierran. \nNo se puede empezar con ^ entre otras cosas \n(Si puede poner espacios)");
      } catch(const InputExceptions::OperationCanceledException& ex){
        this->errorMessage("Operación Cancelada.\nRegresando...");
        return;
      }
    }
    // Convertir y mostrar la Expresión
    this->transformer.transformToPosfija();
    oss << this->insertColorText(" ✅ La conversion es: ", "green") << this->transformer.postFixToString() << endl;
    // Agregarla al Historial
    this->record.insertData(
        this->record.getLastPos(),
        infixNotation + "   ->   " + this->transformer.postFixToString());
    oss << this->insertColorText(" 📈 Conversion agregada al historial.","yellow") << endl << endl;
    oss << this->divider("-");

    oss << this->insertColorText(" 🔁 ¿Desea Realizar Otra Conversión? (S/N): ", "magenta");
    
    repeater = this->readChar(oss.str(), "S,N");

  } while(repeater != 'N');
}

void Menu::showRecord() {

  if (this->record.isEmpty()) {
    this->errorMessage("No Existen Transformaciones Realizadas\nRealice alguna antes de entrar aquí.");
    return;
  } 

  this->cleanScreen();

  cout << this->windowHeader("Historial de Tranformaciones");
  cout << this->insertColorText(this->centerText(this->record.toString()), "cyan");
  
  cout << this->divider("-");

  system("PAUSE");
}

void Menu::deleteRecords() {
  if (this->record.isEmpty()) {
    this->errorMessage("No Existen Transformaciones Realizadas\nRealice alguna antes de entrar aquí.");
    return;
  } 

  ostringstream oss;
  char response;

  this->cleanScreen();
  oss << this->windowHeader("Eliminar Historial");
  this->centerText(this->insertColorText("Actualmente Hay Un Total de: " + to_string(this->record.getTotalElements()) + " Registros", "cyan"));
  this->divider("-");
  oss << this->insertColorText(" ❌ Esta seguro que desea eliminar el historial de transformaciones? (S/N): ", "red");

  response = this->readChar(oss.str(), "S,N");

  if (response == 'S') {
    this->record.deleteAll();
    oss << this->centerText(this->insertColorText("Historial Eliminado Con Exito!", "yellow")) << endl;
  } else {
    oss << this->centerText(this->insertColorText("Operación Cancelada.", "yellow")) << endl;
  }

  cout << oss.str();
  system("PAUSE");
  return;
}

void Menu::exitScreen() {
  this->cleanScreen();

  cout << this->windowHeader("  Saliendo del Programa");
  cout << this->insertColorText("    Programa Hecho Por: ", "cyan") << "Mariscal Rodríguez Omar Jesús" << endl;
  cout << this->insertColorText("    Profesor: ", "cyan") << "Gutiérrez Hernández Alfredo" << endl;
  cout << this->divider("-");
  cout << " 👋 Tenga un buen dia :D" << endl << endl;

  system("PAUSE");
}

Menu::Menu()
    : transformer(*new NotationTransformer), record(*new List<StringWrapper>) {
  mainMenu();
}

Menu::Menu(NotationTransformer& t,
                                                 List<StringWrapper>& r)
    : transformer(t), record(r) {
  mainMenu();
}

Menu::Menu(
    const Menu& other)
    : transformer(other.transformer), record(other.record) {
  mainMenu();
}

Menu::~Menu() = default;

void Menu::mainMenu() {
  ostringstream oss;
  string colorChars("cyan"), colorOps("white"), colorAns("yellow");
  bool op = true;
  oss << this->windowHeader(this->insertColorText("   ✏️  Tranformador de Notacion Infija a Postfija", "green"));
  oss << this->centerText("Por favor, seleccione una opción: ");
  oss << this->divider("-");
  oss << this->insertColorText("    [T]", colorChars) << this->insertColorText(" 🧮 Transformar una Notación", colorOps) << endl;
  oss << this->insertColorText("    [R]", colorChars) << this->insertColorText(" 📈 Revisar el Historial de Transformaciones", colorOps) << endl;
  oss << this->insertColorText("    [E]", colorChars) << this->insertColorText(" ❌ Eliminar el Historial de Transformaciones", colorOps) << endl;
  oss << this->insertColorText("    [S]", colorChars) << this->insertColorText(" 👋 Salir del Programa", colorOps) << endl;
  oss << this->divider("-");
  oss << this->insertColorText("Elección (T,R,E,S): ", colorAns); 

  while (op) {
    this->cleanScreen();
    op = this->handleOption(oss.str());
  }
}


