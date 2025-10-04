#include "menu.hpp"

using namespace std;
void Menu::enterToContinue() {
  cout << "[Enter] para continuar..." << endl;
  getchar();
}

int Menu::readInteger(string oss,
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
      enterToContinue();
    } catch (const InputExceptions::InvalidOption& msg) {
      system("CLS");
      cout << msg.what() << endl;
      enterToContinue();
    }
  }

  return result;
}

char Menu::readChar(const std::string& prompt, const char* posibilities) {
  char result, comparation;

  while (true) {
    int i = 0;
    system("CLS");
    cout << prompt;
    cin >> result;

    result = toupper(result);
    do {
      comparation = *(posibilities + i);
      if (result == comparation)
        return result;
      i++;
    } while (comparation != '\0');

    system("CLS");
    cout << "Opcion Invalida" << endl;
    cout << "Intentelo Nuevamente" << endl;
    system("PAUSE");
  }
}

bool Menu::handleOption(const char& op) {
  system("CLS");

  switch (op) {
    case 'A':
      this->comparator.generateRandomData();
      cout << "Dataset generado Correctamente!" << endl;
      this->enterToContinue();
      return true;
      break;
    case 'B':
      this->runSingleBenchmark("BubbleSort");
      return true;
      break;
    case 'C':
      this->runSingleBenchmark("InsertSort");
      return true;
      break;
    case 'D':
      this->runSingleBenchmark("SelectSort");
      return true;
      break;
    case 'E':
      this->runSingleBenchmark("ShellSort");
      return true;
      break;
    case 'F':
      this->runSingleBenchmark("MergeSort");
      return true;
      break;
    case 'G':
      this->runSingleBenchmark("QuickSort");
      return true;
      break;
    case 'H':
      this->runAllBenchmarks();
      return true;
      break;
    case 'S':
      cout << "Saliendo del Programa..." << endl;
      return false;
      break;
    default:
      this->invalidOption();
      return true;
      break;
  }
}

string Menu::windowHeader(const int& widthBorder, const string& prompt) const {
  ostringstream oss;

  oss << left << setfill('=') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  // Título de Ventana
  oss << setw(widthBorder / 2 - (prompt.size() / 2)) << "| " << prompt
      << setw((widthBorder / 2) - (prompt.size() / 2) - 2) << "" << "|" << endl;
  oss << setfill('-') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  return oss.str();
}

void Menu::invalidOption() {
  system("CLS");
  cout << "+-------------------------------------------------------+" << endl;
  cout << "+                 Opcion Incorrecta                     +" << endl;
  cout << "+               Intentelo Nuevamente                    +" << endl;
  cout << "+-------------------------------------------------------+" << endl;
  this->enterToContinue();
}

void Menu::mainMenu() {
  ostringstream oss;
  bool repeater = true;
  char options[9] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'S'}, op;

  do {
    oss.clear();
    oss.str("");
    system("CLS");
    oss << windowHeader(70, "BENCHMARKS DE ORDENAMIENTOS");
    oss << "Seleccione una de las siguientes opciones: " << endl;
    oss << "[A] Generar un nuevo dataset aleatorio." << endl;
    oss << "[B] Benchmark a BubbleSort" << endl;
    oss << "[C] Benchmark a InsertSort" << endl;
    oss << "[D] Benchmark a SelectSort" << endl;
    oss << "[E] Benchmark a ShellSort (Con secuencia Fibonacci)" << endl;
    oss << "** ** *Algoritmos Recursivos* ** **" << endl;
    oss << "[F] Benchmark a MergeSort" << endl;
    oss << "[G] Benchmark a QuickSort" << endl;
    oss << "[H] Realizar un Benchmark General" << endl << endl;
    oss << "[S] salir del Programa" << endl;
    oss << "Seleccione una opcion: ";

    op = this->readChar(oss.str(), options);
    cin.ignore();
    this->handleOption(op);
  } while (repeater);
}

void Menu::runSingleBenchmark(std::string algorithm) {
  system("CLS");
  cout << "Ordenando " << ListConfigure::ARRAYSIZE << " Elementos Mediante "
       << algorithm << endl;
  if (!this->comparator.getWorkingList().isSorted()) {
    cout << "Desorden de la Lista Verificado" << endl;
    cout << "Ordenamiento por " << algorithm << " en proceso..." << endl;

    if (algorithm == "BubbleSort")
      this->comparator.runSingleBenchmark(
          "BubbleSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {
            list.sortDataBubble();
          });
    if (algorithm == "InsertSort")
      this->comparator.runSingleBenchmark(
          "InsertSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {
            list.sortDataInsert();
          });
    if (algorithm == "SelectSort")
      this->comparator.runSingleBenchmark(
          "SelectSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {
            list.sortDataSelect();
          });
    if (algorithm == "ShellSort")
      this->comparator.runSingleBenchmark(
          "ShellSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {
            list.sortDataShell();
          });
    if (algorithm == "MergeSort")
      this->comparator.runSingleBenchmark(
          "MergeSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {
            list.sortDataMerge();
          });
    if (algorithm == "QuickSort")
      this->comparator.runSingleBenchmark(
          "QuickSort", [](List<Integer, ListConfigure::ARRAYSIZE>& list) {
            list.sortDataQuick();
          });

    cout << "Ordenamiento Terminado" << endl;
    cout << "Comprobando Correcto Ordenamiento..." << endl;
    if (this->comparator.getWorkingList().isSorted()) {
      cout << "Se comprobo que la lista esta ordenada correctamente" << endl;
      cout << "Resultados..." << endl << endl;
      cout << this->comparator.getSingleTable(
          *this->comparator.getResults().retrieve(
              this->comparator.getResults().getLastPosition()));
    } else
      cout << "El Ordenamiento no fue Exitoso" << endl;

  } else {
    cout << "El arreglo esta ordenado\n Se recomienda generar una nueva "
            "sucesion de numeros"
         << endl;
  }

  this->enterToContinue();
}

void Menu::runAllBenchmarks() {
  system("CLS");
  cout << "Ejecutando todos los ordenamientos..." << endl;
  cout << "Este proceso puede tardar un poco de tiempo..." << endl;
  this->comparator.runAllBenchmarks();
  cout << "Ordenamientos Concluidos." << endl;
  cout << "Resultados: " << endl;
  cout << this->comparator.getResultsTable();
  this->enterToContinue();
}

Menu::Menu() : comparator(*new SortingBenchmark) {
  this->mainMenu();
}

Menu::Menu(SortingBenchmark& c) : comparator(c) {
  this->mainMenu();
}

Menu::Menu(const Menu& other) : comparator(other.comparator) {
  this->mainMenu();
}
