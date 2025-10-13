#include "menu.hpp"

using namespace std;

Menu::Menu() : songList(*new List<Song>) {
  mainMenu();
}

Menu::Menu(const Menu& other) : songList(other.songList) {
  mainMenu();
}

Menu::Menu(List<Song>& s) : songList(s) {
  mainMenu();
}

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

Name Menu::readName(string prompt) {
  Name result;
  result.setFirst(readLinePrompt(prompt));
  prompt += result.getFirst() + "\n";
  result.setLast(readLinePrompt(prompt + "Ingrese el Apellido: "));

  return result;
}

string Menu::readLinePrompt(const string& prompt, bool allowEmpty) {
  string result;
  while (true) {
    system("CLS");
    cout << prompt;
    getline(cin, result);
    if (!allowEmpty && result.empty()) {
      system("CLS");
      cout << "No puede estar vacio.\nIntentelo nuevamente." << endl;
      enterToContinue();
      continue;
    }
    return result;
  }
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

bool Menu::handleOption(const std::string& promt) {
  string response;

  system("CLS");
  cout << promt;
  getline(cin, response);

  if (response.empty())
    return true;

  // Hacer las letras mayúsculas
  char option =
      static_cast<char>(std::toupper(static_cast<unsigned char>(response[0])));

  // buscar primer dígito después de la letra (saltando espacios)
  std::size_t pos = 1;
  while (pos < response.size() &&
         std::isspace(static_cast<unsigned char>(response[pos])))
    ++pos;

  bool hasNumber = false;
  int index = -1;
  if (pos < response.size() &&
      std::isdigit(static_cast<unsigned char>(response[pos]))) {
    std::size_t start = pos;
    std::size_t end = start;
    while (end < response.size() &&
           std::isdigit(static_cast<unsigned char>(response[end])))
      ++end;
    std::string numstr = response.substr(start, end - start);
    try {
      index = std::stoi(numstr);
      hasNumber = true;
    } catch (...) {
      hasNumber = false;
    }
  }

  switch (option) {
    case 'A':
      this->insertSong();
      break;

    case 'B':
      if (!hasNumber) {
        system("CLS");
        std::cout << "Falta numero de posicion. Ej: B2\n";
        this->enterToContinue();
        break;
      }
      if (!this->songList.isValidPosition(index)) {
        system("CLS");
        std::cout << "Posicion de lista invalida\n";
        this->enterToContinue();
        break;
      }
      this->editSong(index);
      break;

    case 'C':
      if (!hasNumber) {
        system("CLS");
        std::cout << "Falta numero de posicion. Ej: C12\n";
        this->enterToContinue();
        break;
      }
      if (!this->songList.isValidPosition(index)) {
        system("CLS");
        std::cout << "Posicion de lista invalida\n";
        this->enterToContinue();
        break;
      }
      this->deleteSong(index);
      break;

    case 'D':
      if (!hasNumber) {
        system("CLS");
        std::cout << "Falta numero de posiciin. Ej: D12\n";
        this->enterToContinue();
        break;
      }
      if (!this->songList.isValidPosition(index)) {
        system("CLS");
        std::cout << "Posicion de lista invalida\n";
        this->enterToContinue();
        break;
      }
      system("CLS");
      {
        Song* s = this->songList.retrieve(index);
        if (s)
          std::cout << s->toStringOnly();
        else
          std::cout << "Cancion no encontrada\n";
      }
      this->enterToContinue();
      break;
    case 'E':
      this->deleteAllSongs();
      break;
    case 'F':
      this->saveToDisk();
      break;
    case 'G':
      this->readFromDisk();
      break;
    case 'H':
      this->searchMenu();
      break;
    case 'I':
      this->sortMenu();
      break;
    case 'J':
      this->exitProgram();
      return false;

    default:
      system("CLS");
      std::cout << "Comando invalido\nIntentelo nuevamente.\n";
      enterToContinue();
      break;
  }  // switch

  return true;
}

std::string Menu::songTable(const int& widthRanking,
                            const int& widthSongName,
                            const int& widthName,
                            const int& widthMP3) const {
  ostringstream oss;

  int widthBorder =
      widthRanking + widthSongName + (widthName * 2) + widthMP3 + 16;

  oss << windowHeader(widthBorder, "LISTA DE EXITOS");
  oss << "| " << "# En Lista" << setw(3) << "| " << "Ranking"
      << setw(widthRanking - 7) << "| " << "Nombre de la Cancion"
      << setw(widthSongName - 20) << "| " << "Nombre del Artista"
      << setw(widthName - 18) << "| " << "Nombre del Interprete"
      << setw(widthName - 21) << "| " << "Nombre del MP3" << setw(widthMP3 - 14)
      << "|" << endl;

  oss << setfill('-');
  oss << setw(widthBorder) << " ";
  oss << setfill(' ') << endl;

  oss << this->songList.toString();

  oss << setfill('-');
  oss << setw(widthBorder) << " ";
  oss << setfill(' ');
  oss << endl;

  return oss.str();
}

void Menu::noDataMessage() {
  cout << "+-------------------------------------------------------+" << endl;
  cout << "+            No hay Canciones Registradas Aun           +" << endl;
  cout << "+              Regresando al Menu...                    +" << endl;
  cout << "+-------------------------------------------------------+" << endl;
  this->enterToContinue();
}

void Menu::mainMenu() {
  ostringstream oss;
  bool running = true;

  while (running) {
    system("CLS");

    // Limpiar el ostringstream
    oss.str("");
    oss.clear();

    oss << this->songTable();
    oss << "Opciones: \n";
    oss << "[A] Agregar una Cancion.  [B<n>] Editar una Cancion [C<n>] "
           "Eliminar "
           "una Cancion. [D<n>]  Mostrar Detalles de Cancion.  [E]    Eliminar "
           "Todas las Canciones. \n\n"
           "[F] Guardar la Database   [G] Leer del Disco   "
           "[H] Buscar una Cancion    [I] Ordenar Lista  [J] Salir.\n\n";
    oss << "Seleccione un Comando: ";

    running = handleOption(oss.str());
  }
}

void Menu::insertSong() {
  int widthBorder = 100;
  Song newSong;
  string myString("");
  int myInt(0);
  Name myName;
  ostringstream oss;

  do {
    system("CLS");
    // Linea Exterior
    oss << windowHeader(widthBorder, "INSERTAR EXITO");

    oss << "Ingrese el Nombre de la Cancion: ";
    myString = this->readLinePrompt(oss.str(), false);
    newSong.setSongName(myString);
    oss << newSong.getSongName() << endl;

    oss << "Ingrese el Ranking de la Cancion: ";

    while (true) {
      try {
        system("CLS");
        myInt = readInteger(oss.str(), 0, 3000);
        newSong.setRanking(myInt);
        if (songList.findDataL(newSong) != -1)
          throw std::invalid_argument("Ranking ya utilizado");
        break;
      } catch (const InputExceptions::InvalidOption& msg) {
        system("CLS");
        cout << msg.what() << endl;
        enterToContinue();
      } catch (const std::invalid_argument& msg) {
        system("CLS");
        cout << msg.what() << endl;
        enterToContinue();
      }
    }

    oss << newSong.getRanking() << endl;
    oss << "Ingrese el Nombre del Autor: ";
    myName = readName(oss.str());
    oss << myName.getFirst() << endl;
    oss << "Ingrese el Apellido: " << myName.getLast() << endl;

    newSong.setAuthor(myName);

    oss << "Ingrese el Nombre del Interprete: ";
    myName = readName(oss.str());
    oss << myName.getFirst() << endl;
    oss << "Ingrese el Apellido: " << myName.getLast() << endl;

    newSong.setInterpreter(myName);

    oss << "Ingrese el nombre del Archivo MP3: ";
    myString = this->readLinePrompt(oss.str(), false);
    newSong.setMp3Name(myString);
    oss << newSong.getMp3Name() << endl;

    if (songList.isEmpty())
      songList.insertElement(newSong, 0);
    else {
      oss << "Ingrese la posicion en la lista que tendra la cancion: ";
      while (true) {
        try {
          myInt = readInteger(oss.str(), 0, 49);
          songList.insertElement(newSong, myInt);
          oss << myInt << endl;
          break;
        } catch (const DataContainersExceptions::InvalidPosition& msg) {
          system("CLS");
          cout << msg.what() << endl;
          cout << "Intente Nuevamente." << endl;
          enterToContinue();
        } catch (const DataContainersExceptions::MemoryOverflow& msg) {
          system("CLS");
          cout << msg.what() << endl;
          cout << "Regresando..." << endl;
          enterToContinue();
          return;
        }
      }
    }

    oss << "Cancion Agregada con Exito!." << endl;
    oss << "Desea Agregar Otra Cancion? (1. Si / 2. No): ";

    myInt = readInteger(oss.str(), 1, 2);

    oss.str("");
    oss.clear();
  } while (myInt != 2);
}

void Menu::deleteSong(const int& position) {
  system("CLS");
  ostringstream oss;
  int response;

  Song* target = songList.retrieve(position);
  oss << target->toStringOnly();
  oss << "Esta seguro que desea eliminar esta cancion? (1. Si/ 2. No): ";
  response = readInteger(oss.str(), 1, 2);
  if (response == 1) {
    songList.deleteData(position);
    oss << endl << "Cancion Eliminada con Exito!" << endl;
  } else
    oss << endl << "Operacion Cancelada" << endl;

  system("CLS");
  cout << oss.str();

  enterToContinue();
}

void Menu::deleteAllSongs() {
  system("CLS");
  if (songList.getLastPosition() == -1) {
    cout << "Aun no hay canciones para eliminar" << endl;
    enterToContinue();
    return;
  }

  ostringstream oss;
  int widhtBorder = 50;

  oss << windowHeader(widhtBorder, "ELIMINAR TODAS LAS CANCIONES");

  oss << "Esta seguro que desea eliminar las " << songList.getLastPosition() + 1
      << " canciones? (1. Si/ 2. No): ";
  int response = readInteger(oss.str(), 1, 2);
  system("CLS");
  if (response == 1) {
    songList.deleteAll();
    cout << "Canciones eliminadas con Exito!" << endl;
    cout << "Base de Datos Vacia." << endl;
  } else {
    cout << "Operacion Cancelada." << endl;
  }
  enterToContinue();
}

void Menu::editSong(const int& position) {
  ostringstream oss;
  Song* target = songList.retrieve(position);
  int editOption, newRanking;
  string dataString;
  Name newName;
  Song ver;

  oss << target->toStringOnly();
  oss << "6 Salir\n";

  editOption = readInteger(
      oss.str() + "Elige el atributo que quieras cambiar (1-6): ", 1, 6);

  switch (editOption) {
    case 1:
      oss << "Ingrese el Nuevo Ranking de la Cancion: ";
      newRanking = readInteger(oss.str(), 1, 50);
      ver.setRanking(newRanking);
      if (this->songList.findDataL(ver) != -1) {
        system("CLS");
        cout << "El ranking ya esta ocupado" << endl;
        enterToContinue();
        break;
      }
      target->setRanking(newRanking);
      cout << "Cambio hecho con Exito!";
      break;
    case 2:
      oss << "Ingrese el nuevo nombre de la cancion: ";
      dataString = readLinePrompt(oss.str());
      target->setSongName(dataString);
      cout << "Cambio hecho con Exito!";
      enterToContinue();
      break;
    case 3:
      oss << "Ingrese el nuevo autor de la cancion: ";
      newName = readName(oss.str());
      target->setAuthor(newName);
      cout << "Cambio hecho con Exito!";
      break;
    case 4:
      oss << "Ingrese el nuevo interprete de la cancion: ";
      newName = readName(oss.str());
      target->setInterpreter(newName);
      cout << "Cambio hecho con Exito!";
      break;
    case 5:
      oss << "Ingrese el nuevo nombre del Archivo MP3: ";
      dataString = this->readLinePrompt(oss.str());
      target->setMp3Name(dataString);
      cout << "Cambio Hecho con Exito!";
      break;
    case 6:
      return;
    default:
      break;
  }
  enterToContinue();
}

void Menu::exitProgram() {
  system("CLS");
  int response;
  ostringstream oss;
  if (!this->songList.isEmpty()) {
    oss << windowHeader(50, "SALIR SIN GUARDAR?");
    response = readInteger(
        oss.str() +
            "Desea Guardar las canciones antes de Salir? (1. Si/ 2. No): ",
        1, 2);
    if (response == 1)
      saveToDisk();
  }

  system("CLS");
  std::cout << "Saliendo del Programa.\nTenga un Lindo Dia :D\n";
  enterToContinue();
}

void Menu::searchMenu() {
  system("CLS");
  if (this->songList.isEmpty()) {
    this->noDataMessage();
    return;
  }

  ostringstream oss;
  char op;
  oss << windowHeader(50, "BUSCAR CANCION");
  oss << "Existen un total de: " << this->songList.getLastPosition() + 1
      << " registradas." << endl;
  oss << "A continuacion se muestran las opciones de busqueda: " << endl;
  oss << "[A] Buscar por Nombre de Cancion" << endl
      << "[B] Buscar por Nombre del Inteprete" << endl
      << "[R] Regresar." << endl
      << "Seleccione una Opcion: ";

  while (op != 'R') {
    system("CLS");
    cout << oss.str();
    cin >> op;
    cin.ignore();

    op = toupper(op);

    switch (op) {
      case 'A':
        this->searchBySongName();
        break;
      case 'B':
        this->searchByIntepreter();
        break;
      case 'R':
        system("CLS");
        cout << "Regresando...";
        enterToContinue();
        break;
      default:
        system("CLS");
        cout << "Opcion invalida" << endl;
        cout << "Intentelo nuevamente" << endl;
        enterToContinue();
        break;
    }
  }
}

void Menu::searchBySongName() {
  List<Song> songWithTheName;
  List<Song> auxList = this->songList;
  ostringstream oss;
  char response, options[2] = {'B', 'L'};
  string songName;
  Song searchedSong;
  int position, repeat;

  do {
    oss.str("");
    oss.clear();
    system("CLS");
    oss << windowHeader(50, "BUSCAR POR NOMBRE DE CANCION");
    oss << "Ingrese el nombre de la cancion que quiera buscar: ";

    songName = readLinePrompt(oss.str(), false);
    searchedSong.setSongName(songName);
    oss << songName << endl;

    oss << "Desea Realizar Una Busqueda Binaria o Lineal? (L/B): ";

    response = readChar(oss.str(), options);
    cin.ignore();
    oss << response << endl;

    if (response == 'L') {
      try {
        while (true) {
          position = auxList.findDataL(searchedSong, Song::compareBySongName);
          songWithTheName.insertSortedData(*auxList.retrieve(position));
          auxList.deleteData(position);
        }
      } catch (const DataContainersExceptions::InvalidPosition& ex) {
        // No hacer nada
      }
    } else {
      try {
        while (true) {
          position = auxList.findDataB(searchedSong, Song::compareBySongName);
          songWithTheName.insertSortedData(*auxList.retrieve(position));
          auxList.deleteData(position);
        }
      } catch (const DataContainersExceptions::InvalidPosition& ex) {
        // No hacer nada
      }
    }

    if (songWithTheName.isEmpty())
      oss << "\nNo existe un registro de una cancion llamada: " << songName
          << endl;
    else {
      oss.str("");
      oss.clear();
      oss << this->windowHeader(146, "LISTA DE EXITOS");
      oss << "| " << "# En Lista" << setw(3) << "| " << "Ranking" << setw(3)
          << "| " << "Nombre de la Cancion" << setw(15) << "| "
          << "Nombre del Artista" << setw(12) << "| " << "Nombre del Interprete"
          << setw(9) << "| " << "Nombre del MP3" << setw(11) << "|" << endl;

      oss << setfill('-');
      oss << setw(146) << " ";
      oss << setfill(' ') << endl;
      oss << songWithTheName.toString();

      oss << setfill('-');
      oss << setw(146) << "";
      oss << setfill(' ') << endl;
    }

    songWithTheName.deleteAll();
    oss << "Desea Realizar Otra Busqueda?: (1.Si / 2.No): ";

    repeat = readInteger(oss.str(), 1, 2);

  } while (repeat != 2);
  system("CLS");
  cout << "Regresando..." << endl;
  this->enterToContinue();
}

void Menu::searchByIntepreter() {
  List<Song> songsOfInterpreter;
  List<Song> auxList = this->songList;
  ostringstream oss;
  char response, options[2] = {'B', 'L'};
  string dataString;
  Name searchedName;
  Song searchedSong;
  int position, repeat;

  do {
    oss.str("");
    oss.clear();
    system("CLS");
    oss << windowHeader(70, "BUSCAR POR INTERPRETE DE LA CANCION");

    oss << "Ingrese el Nombre del Interprete: ";
    searchedName = readName(oss.str());
    oss << searchedName.getFirst() << endl;
    oss << "Ingrese el Apellido: " << searchedName.getLast() << endl;

    searchedSong.setInterpreter(searchedName);

    oss << "Desea Realizar Una Busqueda Binaria o Lineal? (L/B): ";

    response = readChar(oss.str(), options);
    cin.ignore();
    oss << response << endl;

    if (response == 'L') {
      try {
        while (true) {
          position =
              auxList.findDataL(searchedSong, Song::compareByInterpreter);
          songsOfInterpreter.insertSortedData(*auxList.retrieve(position));
          auxList.deleteData(position);
        }
      } catch (const DataContainersExceptions::InvalidPosition& ex) {
        // No hacer nada
      }
    } else {
      try {
        while (true) {
          position =
              auxList.findDataB(searchedSong, Song::compareByInterpreter);
          songsOfInterpreter.insertSortedData(*auxList.retrieve(position));
          auxList.deleteData(position);
        }
      } catch (const DataContainersExceptions::InvalidPosition& ex) {
        // No hacer nada
      }
    }

    if (songsOfInterpreter.isEmpty())
      oss << "\nNo existe un registro de una cancion del interprete: "
          << searchedName.toString() << endl;
    else {
      oss.str("");
      oss.clear();
      oss << windowHeader(146, "LISTA DE EXITOS");
      oss << "| " << "# En Lista" << setw(3) << "| " << "Ranking" << setw(3)
          << "| " << "Nombre de la Cancion" << setw(15) << "| "
          << "Nombre del Artista" << setw(12) << "| " << "Nombre del Interprete"
          << setw(9) << "| " << "Nombre del MP3" << setw(11) << "|" << endl;

      oss << setfill('-');
      oss << setw(146) << " ";
      oss << setfill(' ') << endl;
      oss << songsOfInterpreter.toString();

      oss << setfill('-');
      oss << setw(146) << "";
      oss << setfill(' ') << endl;
    }
    songsOfInterpreter.deleteAll();
    oss << "Desea Realizar Otra Busqueda?: (1.Si / 2.No): ";

    repeat = readInteger(oss.str(), 1, 2);

  } while (repeat != 2);
  system("CLS");
  cout << "Regresando..." << endl;
  enterToContinue();
}

void Menu::sortMenu() {
  system("CLS");
  if (this->songList.isEmpty()) {
    this->noDataMessage();
    return;
  }

  if (this->songList.getLastPosition() == 0) {
    cout << "Solo hay 1 cancion registrada." << endl;
    cout << "No se requiere Ordenamiento." << endl;
    enterToContinue();
    return;
  }

  ostringstream oss;
  char op;
  oss << windowHeader(50, "ORDENAR EXITOS");
  oss << "Existen un total de: " << this->songList.getLastPosition() + 1
      << " registradas." << endl;
  oss << "A continuacion se muestran las opciones sobre las cuales ordenar las "
         "canciones: "
      << endl;
  oss << "[A] Ordenar por Nombre de Cancion" << endl
      << "[B] Ordenar por Nombre del Inteprete" << endl
      << "[C] Ordenar por Numero de Ranking" << endl
      << "[R] Regresar." << endl
      << "Seleccione una Opcion: ";

  while (op != 'R') {
    char charsValid[] = {'A', 'B', 'C', 'R'};
    op = readChar(oss.str(), charsValid);
    cin.ignore();

    switch (op) {
      case 'A':
        this->sortBySongName();
        break;
      case 'B':
        this->sortByInterpreter();
        break;
      case 'C':
        this->sortByRanking();
        break;
      case 'R':
        system("CLS");
        cout << "Regresando...";
        enterToContinue();
        break;
    }
  }
}

void Menu::sortBySongName() {
  system("CLS");
  ostringstream oss;
  char op, validOptions[5] = {'A', 'B', 'C', 'D', 'E'};

  oss << windowHeader(100, "Ordenar por Nombre de la Cancion");
  oss << "A continuacion, eliga un algoritmo de ordenamiento para la lista: "
      << endl;
  oss << "[A] Ordenamiento por Burbuja" << endl;
  oss << "[B] Ordenamiento por InsertSort" << endl;
  oss << "[C] Ordenamiento por SelectSort" << endl;
  oss << "[D] Ordenamiento por ShellSort" << endl;
  oss << "[E] Regresar" << endl << endl;
  oss << "Ingrese una Opcion: ";

  op = this->readChar(oss.str(), validOptions);
  cin.ignore();

  oss << op << endl;
  switch (op) {
    case 'A':
      this->songList.sortDataBubble(Song::compareBySongName);
      oss << "Ordenamiento por Burbuja hecho correctamente!." << endl;
      break;
    case 'B':
      this->songList.sortDataInsert(Song::compareBySongName);
      oss << "Ordenamiento por InserSor hecho correctamente!" << endl;
      break;
    case 'C':
      this->songList.sortDataSelect(Song::compareBySongName);
      oss << "Ordenamiento por DataSelect hecho correctamente!" << endl;
      break;
    case 'D':
      this->songList.sortDataShell(Song::compareBySongName);
      oss << "Ordenamiento por ShellSort hecho correctamente!" << endl;
      break;
    case 'E':
      system("CLS");
      cout << "Regresando..." << endl;
      enterToContinue();
      return;
      break;
  }

  system("CLS");
  oss << endl << "Regresando..." << endl << endl;
  cout << oss.str();
  enterToContinue();
}

void Menu::sortByInterpreter() {
  system("CLS");
  ostringstream oss;
  char op, validOptions[5] = {'A', 'B', 'C', 'D', 'E'};

  oss << windowHeader(100, "Ordenar por Interprete de la Cancion");
  oss << "A continuacion, eliga un algoritmo de ordenamiento para la lista: "
      << endl;
  oss << "[A] Ordenamiento por Burbuja" << endl;
  oss << "[B] Ordenamiento por InsertSort" << endl;
  oss << "[C] Ordenamiento por SelectSort" << endl;
  oss << "[D] Ordenamiento por ShellSort" << endl;
  oss << "[E] Regresar" << endl << endl;
  oss << "Ingrese una Opcion: ";

  op = this->readChar(oss.str(), validOptions);
  cin.ignore();

  oss << op << endl;
  switch (op) {
    case 'A':
      this->songList.sortDataBubble(Song::compareByInterpreter);
      oss << "Ordenamiento por Burbuja hecho correctamente!." << endl;
      break;
    case 'B':
      this->songList.sortDataInsert(Song::compareByInterpreter);
      oss << "Ordenamiento por InserSor hecho correctamente!" << endl;
      break;
    case 'C':
      this->songList.sortDataSelect(Song::compareByInterpreter);
      oss << "Ordenamiento por DataSelect hecho correctamente!" << endl;
      break;
    case 'D':
      this->songList.sortDataShell(Song::compareByInterpreter);
      oss << "Ordenamiento por ShellSort hecho correctamente!" << endl;
      break;
    case 'E':
      system("CLS");
      cout << "Regresando..." << endl;
      enterToContinue();
      return;
      break;
  }

  system("CLS");
  oss << endl << "Regresando..." << endl << endl;
  cout << oss.str();
  enterToContinue();
}

void Menu::sortByRanking() {
  system("CLS");
  ostringstream oss;
  char op, validOptions[5] = {'A', 'B', 'C', 'D', 'E'};

  oss << windowHeader(100, "Ordenar por Ranking de la Cancion");
  oss << "A continuacion, eliga un algoritmo de ordenamiento para la lista: "
      << endl;
  oss << "[A] Ordenamiento por Burbuja" << endl;
  oss << "[B] Ordenamiento por InsertSort" << endl;
  oss << "[C] Ordenamiento por SelectSort" << endl;
  oss << "[D] Ordenamiento por ShellSort" << endl;
  oss << "[E] Regresar" << endl << endl;
  oss << "Ingrese una Opcion: ";

  op = this->readChar(oss.str(), validOptions);
  cin.ignore();

  oss << op << endl;
  switch (op) {
    case 'A':
      this->songList.sortDataBubble();
      oss << "Ordenamiento por Burbuja hecho correctamente!." << endl;
      break;
    case 'B':
      this->songList.sortDataInsert();
      oss << "Ordenamiento por InserSor hecho correctamente!" << endl;
      break;
    case 'C':
      this->songList.sortDataSelect();
      oss << "Ordenamiento por DataSelect hecho correctamente!" << endl;
      break;
    case 'D':
      this->songList.sortDataShell();
      oss << "Ordenamiento por ShellSort hecho correctamente!" << endl;
      break;
    case 'E':
      system("CLS");
      cout << "Regresando..." << endl;
      enterToContinue();
      return;
      break;
  }

  system("CLS");
  oss << endl << "Regresando..." << endl << endl;
  cout << oss.str();
  enterToContinue();
}

void Menu::saveToDisk() {
  system("CLS");
  ostringstream oss;

  if (this->songList.isEmpty()) {
    cout << "+-------------------------------------------------------+" << endl;
    cout << "+            No hay Canciones Registradas Aun           +" << endl;
    cout << "+              Regresando al Menu...                    +" << endl;
    cout << "+-------------------------------------------------------+" << endl;
    enterToContinue();
    return;
  }

  int widthBorder = 50;
  string fileName("");
  ofstream file;

  oss << windowHeader(widthBorder, "GUARDAR DATABASE");

  oss << "Ingrese el Nombre que Tendra el Archivo: ";
  fileName = readLinePrompt(oss.str());

  file.open(fileName, ios_base::trunc);

  if (!file.is_open())
    oss << "No se permite la creacion de archivos." << endl;
  else {
    file << this->songList;
    oss << "Database guardada con Exito!" << endl;
  }

  system("CLS");
  cout << oss.str();
  enterToContinue();
}

void Menu::readFromDisk() {
  system("CLS");
  ostringstream oss;
  int widthBorder = 100;
  ifstream file;
  string fileName;

  oss << windowHeader(widthBorder, "LEER ARCHIVO");

  oss << "Tenga en Cuenta que los Archivos se Sobreescribiran" << endl;
  oss << "Ingrese el Nombre del Archivo a Cargar sus Datos: ";

  fileName = readLinePrompt(oss.str());
  oss << fileName << endl;

  file.open(fileName);

  if (!file.is_open())
    oss << "El archivo no existe o no pudo ser abierto" << endl;
  else {
    this->songList.deleteAll();
    file >> this->songList;
    oss << "Archivos Cargados Con Exito!" << endl;
  }

  oss << setfill('=') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  system("CLS");
  cout << oss.str();
  enterToContinue();
}
