#include "menu.hpp"

using namespace std;

Menu::Menu() : songList(*new List<Song>){
  
  mainMenu();
}

Menu::Menu(const Menu& other) : songList(other.songList) {
  mainMenu();
}

Menu::Menu(List<Song>& s) : songList(s) {
  mainMenu();
}


int Menu::readInteger(string oss, const int& lowerLimit, const int& upperLimit) {
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

string Menu::windowHeader(const int& widthBorder, const string& prompt){
  ostringstream oss;

    oss << left << setfill('=') << setw(widthBorder) << "" << endl;
    oss << setfill(' ');

    // Título de Ventana
    oss << setw(widthBorder / 2 - (prompt.size()/2)) << "| " << prompt
        << setw((widthBorder / 2) - (prompt.size()/2)) << "" << "|" << endl;
    oss << setfill('-') << setw(widthBorder) << "" << endl;
    oss << setfill(' ');

    return oss.str();
}

bool Menu::handleOption(const std::string& promt) {
  std::string response;

    system("CLS");
    std::cout << promt;
    std::getline(std::cin, response);

    if (response.empty())
      return true;

    // Hacer las letras mayúsculas
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
        saveToDisk();
        break;
      case 'G':
        readFromDisk();
        break;
      case 'H':
        exitProgram();
        return false;

      default:
        system("CLS");
        std::cout << "Comando invalido\nIntentelo nuevamente.\n";
        system("PAUSE");
        break;
    }  // switch

    return true;
  
}

void Menu::mainMenu() {
  ostringstream oss;
  bool running = true; 

  while(running){
    system("CLS");

    //Limpiar el ostringstream
    oss.str("");
    oss.clear();

    oss << songList.toString();
    oss << "Opciones: \n";
    oss << "[A] Agregar una Cancion.  [B<n>] Editar una Cancion [C<n>] Eliminar "
          "una Cancion. [D<n>] Mostrar Detalles de Cancion. [E] Eliminar Todas las Canciones. \n"
          "[F] Guardar la Database [G] Leer del Disco   [H] Salir.\n";
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

    while (true) {
      try {
        myString = readLinePrompt(oss.str());
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
  system("PAUSE");
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
      dataString = readLinePrompt(oss.str());
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

}

void Menu::exitProgram(){
  system("CLS");
  int response;
  ostringstream oss;
  if(!this->songList.isEmpty()){
    oss << windowHeader(50, "SALIR SIN GUARDAR?");
    response = readInteger(oss.str() + "Desea Guardar las canciones antes de Salir? (1. Si/ 2. No): ",1,2);
    if(response == 1)
      saveToDisk();
  }
  
  system("CLS");
  std::cout << "Saliendo del Programa.\nTenga un Lindo Dia :D\n";
  system("PAUSE"); 
}

void Menu::saveToDisk(){
  system("CLS");
  ostringstream oss;

  if(this->songList.isEmpty()){
    cout << "+-------------------------------------------------------+" << endl;
    cout << "+            No hay Canciones Registradas Aun           +" <<endl;
    cout << "+              No hay datos que Guardar                 +" << endl;
    cout << "+-------------------------------------------------------+" << endl;
    system("PAUSE");
    return;
  }

  int widthBorder = 50;
  string fileName("");
  ofstream file;

  oss << windowHeader(widthBorder, "GUARDAR DATABASE");

  oss << "Ingrese el Nombre que Tendra el Archivo: ";
  fileName = readLinePrompt(oss.str());

  file.open(fileName, ios_base::trunc);

  if(!file.is_open())
    oss << "No se permite la creacion de archivos." << endl;
  else{
    file << this->songList;
    oss << "Database guardada con Exito!" << endl;  
  }

  system("CLS");
  cout << oss.str();
  system("PAUSE");
}

void Menu::readFromDisk(){
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

  if(!file.is_open())
    oss << "El archivo no existe o no pudo ser abierto" << endl;
  else{
    this->songList.deleteAll();
    file >> this->songList;
    oss << "Archivos Cargados Con Exito!" << endl;
  }

  oss << setfill('=') << setw(widthBorder) << "" << endl;
  oss << setfill(' ');

  system("CLS");
  cout << oss.str();
  system("PAUSE");

}
