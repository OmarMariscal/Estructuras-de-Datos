#include "menu.hpp"

void Menu::fillTree() {
  if (!this->bST.isEmpty() && this->warningOverWrite())
    return;

  int capacity;
  Integer numGenerated;
  ostringstream oss;

  try {
    oss << this->windowHeader(" 🌲 LLENAR ÁRBOL CON NÚMEROS ALEATORIOS");
    oss << this->centerText("Ingrese '/r' si quiere regresar");
    oss << this->divider("-");
    oss << this->insertColorText(
        "Ingrese la cantidad de elementos enteros a generar: ", "yellow");
    capacity = this->readPositiveInteger(oss.str());
    oss << capacity << endl;

    this->cleanScreen();
    this->bST.deleteAll();  // Se pone en esta instancia por si antes se cancela
                            // la operación '/r'
    for (int i = 0; i < capacity; i++) {
      numGenerated = RandNumGenerator::randIntGenerator();
      this->bST.addData(numGenerated);
      oss << this->insertColorText("     Numero " + to_string(i + 1) + ": ",
                                   "cyan")
          << numGenerated << endl;
    }

    oss << this->divider("-");
    oss << this->insertColorText(
        this->centerText("✅ ¡Números Generados Con Éxito!"), "green");
    oss << this->divider("-");

    cout << oss.str() << endl;
    system("PAUSE");
  } catch (const InputExceptions::OperationCanceledException& ex) {
    this->errorMessage("Operacion Cancelada\nRegresando...");
    return;
  }
}

void Menu::showRange() {
  this->cleanScreen();
  if (this->bST.isEmpty()) {
    this->errorMessage(
        "Aún no hay registros.\nGenere valores aleatorios antes de verificar "
        "el rango");
    return;
  }

  cout << this->windowHeader("📊 RANGO DE ELEMENTOS DEL BST");
  cout << this->insertColorText("📈 El número de mayor valor generado fue: ",
                                "green")
       << this->bST.getHighest()->getData() << endl;
  cout << this->insertColorText("📉 El número de menor valor generado fue: ",
                                "yellow")
       << this->bST.getLowest()->getData() << endl;
  cout << this->divider("-");
  this->enterToContinue(false);
}

void Menu::showHightSubTrees() {
  this->cleanScreen();
  if (this->bST.isEmpty()) {
    this->errorMessage(
        "Aún no hay registros\nGenere valores aleatorios antes de calcular "
        "alturas");
    return;
  }

  cout << this->windowHeader(
      "📏 ALTURA DE LOS SUBÁRBOLES IZQUIERO Y DERECHO DEL BST");
  cout << this->insertColorText("La altura del subárbol izquierdo es: ",
                                "green")
       << this->bST.getHeight("left") << endl;
  cout << this->insertColorText("La altura del subárbol derecho es: ", "green")
       << this->bST.getHeight("right") << endl;
  cout << this->divider("-");
  this->enterToContinue(false);
}

void Menu::cleanTree() {
  this->cleanScreen();
  if (this->bST.isEmpty()) {
    this->errorMessage("No hay registros que limpiar\nRegresando...");
    return;
  }

  ostringstream oss;
  char response;
  oss << this->windowHeader("🧹 LIMPIAR VALORES DEL BST", 100);
  oss << this->insertColorText(
      "    ¿Esta seguro que desea eliminar todos los registros del árbol? "
      "(S/N): ",
      "red");
  response = this->readChar(oss.str(), "S/N");
  oss << response << endl;

  if (response == 'S') {
    this->bST.deleteAll();
    oss << this->insertColorText(
               "                   ✅ ¡Limpieza realizada con Éxito!", "green")
        << endl;
  } else
    oss << this->insertColorText("Eliminación Cancelada", "yellow") << endl;

  oss << this->divider("-", 100);

  this->cleanScreen();
  cout << oss.str();
  this->enterToContinue(false);
}

void Menu::exitScreen() {
  this->cleanScreen();
  cout << this->windowHeader("👋 SALIENDO DEL PROGRAMA");
  cout << this->insertColorText("Programa Hecho Por: ", "green")
       << "Mariscal Rodríguez Omar Jesús" << endl;
  cout << this->insertColorText("Profesor: ", "yellow")
       << "Hernández Gutiérrez Alfredo" << endl;
  cout << this->divider("-");
  this->enterToContinue(false);
}

bool Menu::handleOption(const std::string& prompt) {
  char op;
  op = this->readChar(prompt, "A,B,C,D,E,F,G,H");

  switch (op) {
    case 'A':
      this->fillTree();
      break;
    case 'B':
      this->showRoute("PREORDER",
                      [this]() -> string { return this->bST.parsePreOrder(); });
      break;
    case 'C':
      this->showRoute("INORDER",
                      [this]() -> string { return this->bST.parseInOrder(); });
      break;
    case 'D':
      this->showRoute("POSTORDER", [this]() -> string {
        return this->bST.parsePostOrder();
      });
      break;
    case 'E':
      this->showRange();
      break;
    case 'F':
      this->showHightSubTrees();
      break;
    case 'G':
      this->cleanTree();
      break;
    case 'H':
      this->exitScreen();
      return false;
      break;
  }
  return true;
}

void Menu::mainMenu() {
  ostringstream oss;
  bool repeater;
  string colorOps("cyan");
  oss << this->windowHeader(" 🌲 ÁRBOL BINARIO DE BÚSQUEDA");
  oss << this->insertColorText(
      this->centerText("Ingrese una de las siguientes opciones"), "green");
  oss << this->divider("-");

  oss << this->insertColorText("    [A]", colorOps)
      << " 🔢 Generar N números aleatorios." << endl;
  oss << this->insertColorText("    [B]", colorOps) << " 🛣️ Recorrido PreOrder"
      << endl;
  oss << this->insertColorText("    [C]", colorOps) << " 📊 Recorrido InOrder"
      << endl;
  oss << this->insertColorText("    [D]", colorOps) << " ⏱️ Recorrido PostOrder"
      << endl;
  oss << this->insertColorText("    [E]", colorOps)
      << " 🎯 Mostrar el Rango de Valores" << endl;
  oss << this->insertColorText("    [F]", colorOps)
      << " 📏 Altura de los Subárboles Izquierdo y Derecho" << endl;
  oss << this->insertColorText("    [G]", colorOps) << " 🧹 Limpiar el Árbol"
      << endl;
  oss << this->insertColorText("    [H]", colorOps) << " 👋 Salir" << endl;
  oss << this->divider("-");
  oss << this->insertColorText("Ingrese una Opción: ", "yellow");

  do {
    repeater = this->handleOption(oss.str());
  } while (repeater);
}

Menu::Menu() : bST(*new AVLTree<Integer>) {
  this->mainMenu();
}

Menu::Menu(const Menu& other) : bST(other.bST) {
  this->mainMenu();
}

Menu::Menu(AVLTree<Integer>& b) : bST(b) {
  this->mainMenu();
}

bool Menu::warningOverWrite() {
  char response;
  ostringstream oss;
  oss << this->windowHeader("⚠️ ¡ADVERTENCIA!");
  oss << this->insertColorText(
      this->centerText("Ya se tienen registros en el árbol"), "red");
  oss << this->insertColorText(
             "Si se quieren generar más, se tendrán que sobreescribir los ya "
             "existentes",
             "red")
      << endl;
  oss << this->divider("-");
  oss << "¿Esta seguro que quiere sobreescribir los datos? (S/N): ";
  response = this->readChar(oss.str(), "S,N");
  return (response == 'N');
}
