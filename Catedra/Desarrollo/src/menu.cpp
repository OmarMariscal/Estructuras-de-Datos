#include "menu.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


std::string Menu::bannerToString() const{
    int year = 2025;
    int month = 8;
    int day = 28;
    std::ostringstream banner;
    banner<< "+-------------------------------------------------------------+\n";
    banner<< " ___            _            _       ___  _      _ _        _ \n";
    banner<< "| _ \\___ __ ___| |_ __ _ _ _(_)___  |   \\(_)__ _(_) |_ __ _| |\n";
    banner<< "|   / -_) _/ -_)  _/ _` | '_| / _ \\ | |) | / _` | |  _/ _` | |\n";
    banner<< "|_|_\\___\\__\\___|\\__\\__,_|_| |_\\___/ |___/|_\\__, |_|\\__\\__,_|_|\n";
    banner<< "                                           |___/               \n";
    banner<< "Autor: Mariscal Rodriguez Omar Jesus. | Fecha: "<<year<<"-"<<month<<"-"<<day<<endl;
    banner<< "+-------------------------------------------------------------+\n";
    
    return banner.str();
}

void Menu::invalidCategory(){
    std::cout << "+------------------------------------------------------------+\n";
    std::cout << "|                         [ERROR]                            |\n";
    std::cout << "|  Categoria invalida.                                       |\n";
    std::cout << "|  Valores validos:                                          |\n";
    std::cout << "|    0 = Desayuno    1 = Comida    2 = Cena    3 = Navideno  |\n";
    std::cout << "|  Ingrese uno de los nimeros anteriores o 0 para cancelar.  |\n";
    std::cout << "+------------------------------------------------------------+\n";

}

void Menu::invalidString(){
    std::cout << "+------------------------------------------------------------+\n";
    std::cout << "|                         [ERROR]                            |\n";
    std::cout << "|  Entrada invalida.                                         |\n";
    std::cout << "|  Asegurese de ingresar texto no vacio y sin simbolos extra.|\n";
    std::cout << "|  Intente nuevamente.                                       |\n";
    std::cout << "+------------------------------------------------------------+\n";
}

void Menu::recipeNotFoundMessage(){
    std::cout << "+--------------------------------------------------------------------------------+\n";
    std::cout << "|                         [ERROR]                                                |\n";
    std::cout << "|  Receta no encontrada.                                                         |\n";
    std::cout << "|  Asegurese de ingresar texto no vacio y que el nombre coincida con un registro.|\n";
    std::cout << "|  Intente nuevamente.                                                           |\n";
    std::cout << "+--------------------------------------------------------------------------------+\n";
    
}

void Menu::showAllRecipes(){
    cout<<bannerToString();
    cout<<"|                           LISTA DE RECETAS (Pagina 1/2)                      |";
    cout << R"(
+------------------------------------------------------------------------------+
|  #  | Nombre                     | Categoria  | Autor          | Tiempo (min) |
|-----+----------------------------+------------+----------------+--------------|
|  1  | Omelette Vegetal           | Desayuno   | Ana Perez      | 15           |
|  2  | Ensalada Cesar             | Comida     | J. Martinez    | 20           |
|  3  | Pavo Navideno              | Navideno   | Chef Luis      | 180          |
|  4  | Spaghetti al Pesto         | Comida     | M. Gomez       | 25           |
|  5  | Sopa de Zanahoria          | Cena       | Lucia Torres   | 30           |
+------------------------------------------------------------------------------+
[N] Siguiente  [P] Anterior  [V <n>] Ver detalle  [B] Volver al menu
Ingrese comando: _
        )";
}

Menu::Menu(){

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

    // Normalize helper to draw a centered line inside the box
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

std::string Menu::mainMenu() const{
    std::ostringstream oss;
    oss<<bannerToString();
    oss<<"|                    MENU PRINCIPAL                           |"<<endl;
    oss<< "+-------------------------------------------------------------+\n";

    oss<<"\nOpcion 1: Agregar Recetas\n";
    oss<<"Opcion 2: Mostrar Recetas\n";
    oss<<"Opcion 3: Modificar Receta\n";
    oss<<"Opcion 4: Buscar Recetas\n";
    oss<<"Opcion 5: Ordenar Recetas (Nombre/Tiempo)\n";
    oss<<"Opcion 6: Opciones de Disco\n";
    oss<<"Opcion 7: Salir\n";
    oss<<"\nEliga una Opcion: ";

    return oss.str();
}

void Menu::addRecipes(){
    cout<<bannerToString();
    cout<<"|                 AGREGAR NUEVA RECETA                         |"<<endl;
    cout<< "+-------------------------------------------------------------+\n";
    std::cout << R"(
Nombre del platillo: _
(0 = cancelar)

Autor (nombre): _
Apellido (opcional): _
Categoria [0 = Desayuno, 1 = Comida,2 = Cena ,3 = Navideno]: _
Tiempo de preparacion (min): _
¿Desea ingresar procedimiento ahora? [S/N]: _
Ingrese procedimiento. Termine con "::end" en una línea:
> Limpiar ingredientes
> Mezclar todo
> Hornear 30 min
> ::end

Ahora agregue ingredientes (minimo 1).
Para terminar ingrese nombre vacio. ('0' = cancelar)

Ingrediente 1 - Nombre: _
Cantidad: _    Unidad: _
[OK] Ingrediente 'Ajo' agregado.

Ingrediente 2 - Nombre: _
Cantidad: _    Unidad: _
[OK] Ingrediente 'Sal' agregado.

...

[OK] Receta 'NombrePlatillo' agregada correctamente.
Presione Enter para continuar...
+------------------------------------------------------------------------------+
    )";

}

void Menu::showRecipes(){
    cout<<bannerToString();
    cout<<"|                    MOSTRAR RECETAS                          |"<<endl;
    cout<< "+-------------------------------------------------------------+";
    
    cout<<"\n| Opcion 1: Mostrar Todas las Recetas                         |";
    cout<<"\n| Opcion 2: Mostrar Recetas Por Categoria                     |";
    cout<<"\n| Eliga una Opcion:                                           |";
    cout<<"\n+-------------------------------------------------------------+";

}

void Menu::showRecipesForCategory(){
    cout<<bannerToString();
    cout<<"|                 RECETAS POR CATEGORIA                        |"<<endl;
    cout<< "+-------------------------------------------------------------+\n";
    std::cout << R"(
+------------------------------------------------------------------------------+
|                          CATEGORIA: COMIDA (Pagina 1/1)                     |
+------------------------------------------------------------------------------+
|  #  | Nombre                             | Autor             | Tiempo (min) |
|-----+------------------------------------+-------------------+--------------|
|  1  | Ensalada Cesar                     | J. Martinez       | 20           |
|  2  | Spaghetti al Pesto                 | M. Gomez          | 25           |
|  3  | Tacos de Pollo                     | Carmen Lopez      | 30           |
|  4  | Lasana de Carne                    | Ricardo Alvarez   | 90           |
|  5  | Filete a la Pimienta               | Laura Santos      | 45           |
|  6  | Arroz con Mariscos                 | Chef Marina       | 40           |
+------------------------------------------------------------------------------+
[V <n>] Ver detalle de la receta numero n   [B] Volver al menu
Ingrese comando: _
)";
}


void Menu::modifyRecipe(){
    cout<<bannerToString();
    cout<<"|                 MODIFICAR RECETA                        |"<<endl;
    cout<< "+-------------------------------------------------------------+\n";
    
    std::cout << R"(
| Receta seleccionada: Pavo Navideno                                           |
| Autor actual       : Chef Luis                                               |
| Categoria actual   : Navideno                                                |
| Tiempo actual (min): 180                                                     |
+------------------------------------------------------------------------------+
| 1) Modificar nombre                                                          |
| 2) Modificar autor (nombre / apellido)                                       |
| 3) Modificar categoria (0=Desayuno,1=Comida,2=Cena,3=Navideno)               |
| 4) Modificar tiempo de preparacion (min)                                     |
| 5) Modificar procedimiento (editor multilinea, termine con '::end')          |
| 6) Administrar ingredientes                                                  |
|    6.1) Agregar ingrediente (insertado ordenado)                             |
|    6.2) Eliminar ingrediente por nombre                                      |
|    6.3) Modificar cantidad de ingrediente                                    |
|    6.4) Eliminar todos los ingredientes                                      |
| 7) Guardar cambios                                                           |
| 0) Cancelar (descartar cambios)                                              |
+------------------------------------------------------------------------------+

Seleccione la opción a ejecutar: _
)";
}

void Menu::pedirNombre(){
    cout<<bannerToString();
    cout<<"|                    MODIFICAR RECETA                          |"<<endl;
    cout<< "+-------------------------------------------------------------+";
    
    cout<<"\n| Ingresa el Nombre de la Receta:                             |";
    cout<<"\n+-------------------------------------------------------------+";

}

void Menu::searchRecipesByName(){

        cout<<bannerToString();
    cout<<"|                       PAVO NAVIDENO                        |"<<endl;
    cout<< "+-------------------------------------------------------------+\n";
     std::cout << R"(
Autor: Chef Luis
Categoría: Navideno
Tiempo de preparación: 180 minutos

Ingredientes (10):
 1) Pavo entero               | 5.0  | kg
 2) Sal                      | 50   | g
 3) Pimienta                 | 20   | g
 4) Ajo                      | 30   | g
 5) Mantequilla              | 200  | g
 6) Tomillo                  | 5    | g
 7) Romero                   | 5    | g
 8) Naranja                  | 3    | piezas
 9) Miel                     | 100  | ml
10) Caldo de pollo           | 500  | ml

Procedimiento:
1. Limpiar y preparar el pavo.
2. Hacer la marinada con ajo, miel y especias.
3. Marinar por 12 horas.
4. Hornear a 180C por 3 horas, marinado con caldo.
5. Reposar y servir.

[A] Agregar ingrediente  [E] Editar receta  [I] Editar ingredientes
[D] Eliminar receta      [B] Volver a lista
Ingrese opcion: _
+------------------------------------------------------------------------------+
)";
}
