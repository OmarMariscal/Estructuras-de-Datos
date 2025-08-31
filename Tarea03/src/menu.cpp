#include "menu.hpp"

using namespace std;

Menu::Menu() {
  mainMenu();
}

Menu::Menu(const Menu& other) : songList(other.songList) {
  mainMenu();
}

Menu::Menu(const List<Song>& s) : songList(s) {
  mainMenu();
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
        throw Exception("Numero Fuera de Rango");
      break;
    } catch (std::invalid_argument) {
      system("CLS");
      cout << "Entrada invalida" << endl;
      cout << "Intente nuevamente" << endl;
      system("PAUSE");
    } catch (Exception msg) {
      system("CLS");
      cout << msg.what() << endl;
      system("PAUSE");
    }
  }

  return result;
}

Name Menu::readName(string prompt) {
  Name result;
  result.setFirst(readLinePrompt(prompt, false));
  prompt += result.getFirst() + "\n";
  result.setLast(readLinePrompt(prompt + "Ingrese el Apellido: ", false));

  return result;
}

string Menu::readLinePrompt(const string& prompt, bool allowEmpty) {
  string result;
  while (true) {
    system("CLS");
    cout << prompt;
    getline(cin, result);
    if (result == "0")
      throw OperationCanceledException();
    if (!allowEmpty && result.empty()) {
      system("CLS");
      cout << "No puede estar vacio.\nIntentelo nuevamente." << endl;
      system("PAUSE");
      continue;
    }
    return result;
  }
}

void Menu::handleOption(const std::string& promt) {
  std::string response;

  while (true) {
    system("CLS");
    std::cout << promt;
    std::getline(std::cin, response);

    if (response.empty()) {
      system("CLS");
      std::cout << "Comando invalido\n";
      system("PAUSE");
      continue;
    }

    // letra de opción (normalizamos a mayúscula)
    char option = static_cast<char>(
        std::toupper(static_cast<unsigned char>(response[0])));

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
        insertSong();
        break;

      case 'B':
        if (!hasNumber) {
          system("CLS");
          std::cout << "Falta numero de posicion. Ej: B2\n";
          system("PAUSE");
          break;
        }
        if (!songList.isValidPosition(index)) {
          system("CLS");
          std::cout << "Posicion de lista invalida\n";
          system("PAUSE");
          break;
        }
        editSong(index);
        break;

      case 'C':
        if (!hasNumber) {
          system("CLS");
          std::cout << "Falta numero de posicion. Ej: C12\n";
          system("PAUSE");
          break;
        }
        if (!songList.isValidPosition(index)) {
          system("CLS");
          std::cout << "Posicion de lista invalida\n";
          system("PAUSE");
          break;
        }
        deleteSong(index);
        break;

      case 'D':
        if (!hasNumber) {
          system("CLS");
          std::cout << "Falta numero de posiciin. Ej: D12\n";
          system("PAUSE");
          break;
        }
        if (!songList.isValidPosition(index)) {
          system("CLS");
          std::cout << "Posicion de lista invalida\n";
          system("PAUSE");
          break;
        }
        system("CLS");
        {
          Song* s = songList.retrieve(index);
          if (s)
            std::cout << s->toString();
          else
            std::cout << "Cancion no encontrada\n";
        }
        system("PAUSE");
        break;
      case 'E':
        deleteAllSongs();
        break;
      case 'F':
        system("CLS");
        std::cout << "Saliendo del Programa.\nTenga un Lindo Dia :D\n";
        system("PAUSE");
        exit(-1);
        return;

      default:
        system("CLS");
        std::cout << "Comando invalido\nIntentelo nuevamente.\n";
        system("PAUSE");
        break;
    }  // switch
  }  // while
}

void Menu::mainMenu() {
  ostringstream oss;
  system("CLS");
  oss << songList.toString();
  oss << "Opciones: \n";
  oss << "[A] Agregar una Cancion.  [B<n>] Editar una Cancion [C<n>] Eliminar "
         "una Cancion. [D<n>] Mostrar Detalles de Cancion. [E] Eliminar Todas "
         "las Canciones. \n[F] Salir.\n";
  oss << "Seleccione un Comando: ";

  handleOption(oss.str());
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
    oss << left << setfill('=') << setw(widthBorder) << "" << endl;
    oss << setfill(' ');

    // Título de Ventana
    oss << setw(widthBorder / 2 - 7) << "| " << "INSERTAR EXITO"
        << setw((widthBorder / 2) - 8) << "" << "|" << endl;
    oss << setfill('-') << setw(widthBorder) << "" << endl;
    oss << setfill(' ');

    oss << "Ingrese el Nombre de la Cancion: ";

    while (true) {
      try {
        myString = readLinePrompt(oss.str(), false);
        newSong.setSongName(myString);
        break;
      } catch (Exception msg) {
        system("CLS");
        cout << msg.what() << endl;
        cout << "Vuelva a intentarlo\n";
        system("PAUSE");
      }
    }

    oss << newSong.getSongName() << endl;
    oss << "Ingrese el Ranking de la Cancion: ";

    while (true) {
      try {
        system("CLS");
        myInt = readInteger(oss.str(), 0, 1000);
        if (!songList.isRankingAvalible(myInt))
          throw std::invalid_argument("Ranking ya utilizado");
        newSong.setRanking(myInt);
        break;
      } catch (Exception msg) {
        system("CLS");
        cout << msg.what() << endl;
        system("PAUSE");
      } catch (std::invalid_argument msg) {
        system("CLS");
        cout << msg.what() << endl;
        system("PAUSE");
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
        } catch (Exception msg) {
          system("CLS");
          cout << msg.what() << endl;
          cout << "Intente Nuevamente." << endl;
          system("PAUSE");
        }
      }
    }

    oss << "Cancion Agregada con Exito!." << endl;
    oss << "Desea Agregar Otra Cancion? (1. Si / 2. No): ";

    myInt = readInteger(oss.str(), 1, 2);

    oss.str("");
    oss.clear();
  } while (myInt != 2);

  mainMenu();
}

void Menu::deleteSong(const int& position) {
  system("CLS");
  ostringstream oss;
  int response;

  Song* target = songList.retrieve(position);
  oss << target->toString();
  oss << "Esta seguro que desea eliminar esta cancion? (1. Si/ 2. No): ";
  response = readInteger(oss.str(), 1, 2);
  if (response == 1) {
    songList.deleteData(position);
    oss << endl << "Cancion Eliminada con Exito!" << endl;
  } else
    oss << endl << "Operacion Cancelada" << endl;

  system("CLS");
  cout << oss.str();

  system("PAUSE");
  mainMenu();
}

void Menu::deleteAllSongs() {
  system("CLS");
  if (songList.getLastPosition() == -1) {
    cout << "Aun no hay canciones para eliminar" << endl;
    system("PAUSE");
    return;
  }

  ostringstream oss;
  int widhtBorder = 50;

  oss << left << setfill('=') << setw(widhtBorder) << "" << endl;
  oss << setfill(' ');
  oss << setw(widhtBorder / 2 - 13) << "| " << "ELIMMINAR TODAS LAS CANCIONES"
      << setw((widhtBorder / 2) - 17) << "" << "|" << endl;
  oss << setfill('=') << setw(widhtBorder) << "" << endl;

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
  system("PAUSE");
  mainMenu();
}

void Menu::editSong(const int& position) {
  ostringstream oss;
  Song* target = songList.retrieve(position);
  int editOption, newRanking;
  string dataString;
  Name newName;

  oss << target->toString();
  oss << "5 Salir\n";

  editOption = readInteger(
      oss.str() + "Elige el atributo que quieras cambiar (1-5): ", 1, 5);

  switch (editOption) {
    case 1:
      oss << "Ingrese el Nuevo Ranking de la Cancion: ";
      newRanking = readInteger(oss.str(), 1, 50);
      if (!songList.isRankingAvalible(newRanking)) {
        system("CLS");
        cout << "El ranking ya esta ocupado" << endl;
        system("PAUSE");
        break;
      }
      target->setRanking(newRanking);
      cout << "Cambio hecho con Exito!";
      break;
    case 2:
      oss << "Ingrese el nuevo nombre de la cancion: ";
      dataString = readLinePrompt(oss.str(), false);
      target->setSongName(dataString);
      cout << "Cambio hecho con Exito!";
      system("PAUSE");
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
      return;
    default:
      break;
  }
  system("PAUSE");

  mainMenu();
}
