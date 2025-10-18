#include "basemenu.hpp"

using namespace std;

int BaseMenu::readInteger(string oss, const int& lowerLimit, const int& upperLimit) {
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

float BaseMenu::readFloat(const std::string& oss, const float& lowerLimit, const float& upperLimit) {
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

Name BaseMenu::readName(string prompt, const string& petition, const string& petition2) {
  Name result;
  prompt += petition;
  result.setFirst(readLinePrompt(prompt));
  prompt += result.getFirst() + "\n";
  prompt += petition2;
  result.setLast(readLinePrompt(prompt));

  return result;
}

string BaseMenu::readLinePrompt(const string& prompt, bool allowEmpty) {
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

char BaseMenu::readChar(const std::string& prompt, const std::string& options) {
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

Category BaseMenu::readCategory(const std::string& prompt){
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

std::string BaseMenu::standarString(std::string text){
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

std::string BaseMenu::clearColor(const std::string& s){
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

void BaseMenu::cleanScreen(){
    system("CLS");
}

void BaseMenu::errorMessage(const std::string& prompt, const int& windowWidth){
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

void BaseMenu::enterToContinue() {
    cout << "+----------------------------------+" << endl;
    cout << "|         Presiones [ENTER]        |" << endl;
    cout << "|           Para Continuar         |" << endl;
    cout << "+----------------------------------+" << endl;
    cin.ignore();
    cin.get();
}


std::string BaseMenu::categoryToString(const Category& category) const{
    switch(category){
        case DESAYUNO: return "desayuno";
        case COMIDA: return "comida";
        case CENA: return "cena";
        case NAVIDEÑO: return "navideño";
    }
    return "";
}

string BaseMenu::windowHeader(const string& prompt, const int& widthBorder, const string& c) const {
    ostringstream oss;
    int spaces((widthBorder - prompt.size()) / 2);

    oss << this->divider(c, widthBorder);
    oss << setw(spaces) << "" << prompt << endl;

    oss << this->divider(c, widthBorder);

  return oss.str();
}

std::string BaseMenu::divider(const std::string& character, const int& size) const {
    std::string line;
    for (int i = 0; i < size; ++i) {
        line += character;
    }
    line += '\n';
    return line;
}

string BaseMenu::insertColorText(std::string prompt, std::string color) {

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

std::string BaseMenu::centerText(string prompt, const int& windowWidth){
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


BaseMenu::~BaseMenu(){}


