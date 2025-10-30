#include "notationtransformermenu.hpp"

using namespace std;

int NotationTransformerMenu::readInteger(string oss,
                                         const int& lowerLimit,
                                         const int& upperLimit) {
  string aux("");
  int result;
  while (true) {
    try {
      system("CLS");
      cout << oss;
      getline(cin, aux);
      result = stoi(aux);

      if (result > upperLimit || result < lowerLimit)
        throw InputExceptions::InvalidOption("Numero Fuera de Rango");
      break;
    } catch (const std::invalid_argument& ex) {
      system("CLS");
      cout << "Entrada invalida" << endl;
      cout << "Intente nuevamente" << endl;
      system("PAUSE");
    } catch (const InputExceptions::InvalidOption& ex) {
      system("CLS");
      cout << ex.what() << endl;
      system("PAUSE");
    }
  }

  return result;
}

string NotationTransformerMenu::windowHeader(const int& widthBorder,
                                             const string& prompt) {
  ostringstream oss;

  oss << left << setfill('=') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  // Título de Ventana
  oss << setw(widthBorder / 2 - (prompt.size() / 2)) << "| " << prompt
      << setw((widthBorder / 2) - (prompt.size() / 2)) << "" << "|" << endl;
  oss << setfill('-') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  return oss.str();
}

void NotationTransformerMenu::enterToContinue() {
  cout << "[Enter] Para Continuar..." << endl;
  getchar();
}

bool NotationTransformerMenu::handleOption(const std::string& promt) {
  std::string response;

  system("CLS");
  std::cout << promt;
  std::getline(std::cin, response);

  if (response.empty())
    return true;

  // Hacer las letras mayúsculas
  char option =
      static_cast<char>(std::toupper(static_cast<unsigned char>(response[0])));

  switch (option) {
    case 'T':
      makeTranformation();
      break;
    case 'R':
      showRecord();
      break;
    case 'E':
      deleteRecords();
      break;
    case 'S':
      exitScreen();
      return false;
      break;

    default:
      system("CLS");
      std::cout << "Comando invalido\nIntentelo nuevamente.\n";
      system("PAUSE");
      break;
  }  // switch

  return true;
}

void NotationTransformerMenu::makeTranformation() {
  string infixNotation;
  Queue<char> queueNotation;

  // Bucle perpetuo hasta que se ingresa una expresión válida
  while (true) {
    try {
      system("CLS");
      cout << windowHeader(50, "Transformar de Notacion Infija a PostFija");
      cout << "Ingrese la operacion en notacion infija: ";
      getline(cin, infixNotation);
      queueNotation = this->transformer.stringToQueue(infixNotation);
      this->transformer.setInflixQueue(queueNotation);
      break;  // Si no hay excepción salimos del bucle.
    } catch (const NotationTransformerExceptions::InvalidExpresion&
                 ex) {  // Manejo de la Excepción Personalizada
      cout << "La expresion no es valida." << endl;
      cout << "Recuerde que no se pueden tener dos operadores juntos (3++5)"
           << endl;
      cout << "Parentesis que no se cierran. No se puede empezar con ^ entre "
              "otras cosas (Si puede poner espacios)"
           << endl
           << endl;
      enterToContinue();
    }
  }
  // Convertir y mostrar la Expresión
  this->transformer.transformToPosfija();
  cout << "La conversion es: " << this->transformer.postFixToString() << endl;
  // Agregarla al Historial
  this->record.insertData(
      this->record.getLastPos(),
      infixNotation + "   ->   " + this->transformer.postFixToString());
  cout << "Conversion agregada al historial." << endl << endl;

  enterToContinue();
}

void NotationTransformerMenu::showRecord() {
  ostringstream oss;
  system("CLS");
  oss << windowHeader(100, "Historial de Tranformaciones");

  if (this->record.isEmpty()) {
    oss << "Aun no se tienen registros de transformaciones" << endl;
    oss << "Regresando al Menu Principal..." << endl;
  } else
    oss << this->record.toString() << endl;

  cout << oss.str();
  enterToContinue();
}

void NotationTransformerMenu::deleteRecords() {
  system("CLS");
  ostringstream oss;
  oss << windowHeader(50, "Eliminar Historial");

  if (this->record.isEmpty()) {
    oss << "No se tienen registros de conversiones aun." << endl;
    oss << "Regresando al Menu Principal." << endl;
    cout << oss.str();
    enterToContinue();
    return;
  }

  int response;
  oss << "Esta seguro que desea eliminar el historial de transformaciones? (1. "
         "Si / 2. No): ";

  response = readInteger(oss.str(), 1, 2);
  system("CLS");

  if (response == 1) {
    this->record.deleteAll();
    oss << endl << "Historial Eliminado Con Exito!" << endl;
  } else {
    oss << endl << "Operacion Cancelada" << endl;
  }
  cout << oss.str();
  enterToContinue();
}

void NotationTransformerMenu::exitScreen() {
  system("CLS");
  ostringstream oss;
  oss << windowHeader(50, "Saliendo del Programa");
  oss << "Programa hecho por: Mariscal Rodriguez Omar Jesus" << endl;
  oss << "Profesor: Gutierrez Hernandez Alfredo" << endl << endl;
  oss << "Tenga un buen dia :D" << endl;

  cout << oss.str();
  enterToContinue();
}

NotationTransformerMenu::NotationTransformerMenu()
    : transformer(*new NotationTransformer), record(*new List<StringWrapper>) {
  mainMenu();
}

NotationTransformerMenu::NotationTransformerMenu(NotationTransformer& t,
                                                 List<StringWrapper>& r)
    : transformer(t), record(r) {
  mainMenu();
}

NotationTransformerMenu::NotationTransformerMenu(
    const NotationTransformerMenu& other)
    : transformer(other.transformer), record(other.record) {
  mainMenu();
}

void NotationTransformerMenu::mainMenu() {
  ostringstream oss;
  bool op = true;
  oss << windowHeader(100, "Tranformador de Notacion Infija a Postfija");
  oss << "Opciones: [T]ransformar una Notacion \n"
      << "          [R]evisar el Historial de Transformaciones\n"
      << "          [E]liminar el Historial de Transformaciones\n"
      << "          [S]alir del Programa\n";
  oss << "Eleccion: ";

  while (op) {
    system("CLS");
    op = handleOption(oss.str());
  }
}
