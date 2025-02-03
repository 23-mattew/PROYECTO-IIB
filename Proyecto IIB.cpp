#include <iostream>
#include <vector>
#include <chrono>
#include <limits>
using namespace std;

const int SIZE = 10;
char laber[SIZE][SIZE] = {
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
    {'_', '|', '|', '_', '|', '|', '|', '|', '|', '_'},
    {'_', '_', '_', '_', '_', '_', '_', '|', '_', '_'},
    {'|', '|', '|', '|', '_', '|', '_', '|', '_', '|'},
    {'_', '_', '_', '_', '_', '|', '_', '|', '_', '_'},
    {'_', '|', '|', '|', '_', '|', '_', '_', '_', 'E'},
    {'_', '_', '_', '|', '_', '_', '|', '|', '_', '_'},
    {'|', '_', '_', '|', '_', '_', '_', '_', '_', '_'},
    {'_', '_', '_', '_', '_', '|', '|', '|', '|', '_'},
    {'S', '_', '_', '_', '_', '_', '_', '_', '_', '_'}
};

// Coordenadas iniciales del jugador
int posicionX = 9, posicionY = 0;

// Estructura para almacenar los datos de los jugadores
struct Player {
    string nombre;
    int puntaje;
};

Player jugadores[3];  // Arreglo para almacenar hasta 3 jugadores
int numJugadores = 0; // N�mero actual de jugadores

// Funci�n para limpiar la pantalla
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");  // Para Windows
    #else
        system("clear");  // Para otros sistemas
    #endif
}

// Funci�n para agregar un nuevo jugador
void agregarJugador() {
    if (numJugadores < 3) {
        string nombreIngresado;
        cout << "Ingresa el nombre del jugador: ";
        
        // Limpiar el b�fer de entrada antes de leer el nombre
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        // Validamos que el nombre no est� vac�o
        while (true) {
            getline(cin, nombreIngresado); // Leer la l�nea completa (incluyendo espacios)
            if (!nombreIngresado.empty()) {
                jugadores[numJugadores].nombre = nombreIngresado;
                break;
            } else {
                cout << "El nombre no puede estar vac�o. Ingresa un nombre v�lido: ";
            }
        }

        jugadores[numJugadores].puntaje = 0;  // Puntaje inicial en 0
        numJugadores++;
    } else {
        cout << "Ya hay 3 jugadores, no se pueden agregar m�s." << endl;
    }
}

// Funci�n para mostrar los puntajes
void mostrarPuntajes() {
    cout << "Puntajes de los jugadores:" << endl;
    for (int i = 0; i < numJugadores; ++i) {
        cout << "Jugador: " << jugadores[i].nombre << " - Puntaje: " << jugadores[i].puntaje << endl;
    }
}

// Funci�n para imprimir el laberinto
void printlaber() {
    limpiarPantalla();  // Limpiar la pantalla antes de imprimir el laberinto
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i == posicionX && j == posicionY)
                cout << 'P'; // Mostrar al jugador
            else
                cout << laber[i][j];
        }
        cout << endl;
    }
}

// Funci�n para mover al jugador
void movePlayer(char direction) {
    int nuevaposX = posicionX, nuevaposY = posicionY;

    // Actualizar las coordenadas seg�n la entrada
    if (direction == 'W' || direction == 'w') {
        nuevaposX--;
    }
    else if (direction == 'S' || direction == 's') {
        nuevaposX++;
    }
    else if (direction == 'A' || direction == 'a') {
        nuevaposY--;
    }
    else if (direction == 'D' || direction == 'd') {
        nuevaposY++;
    }
    else {
        // Si la direcci�n es inv�lida, mostrar un mensaje
        cout << "Ingresa una letra de direccion valida" << endl;
        return; // Salir de la funci�n si la direcci�n es inv�lida
    }

    // Verificar l�mites y colisiones
    if (nuevaposX >= 0 && nuevaposX < SIZE && nuevaposY >= 0 && nuevaposY < SIZE && laber[nuevaposX][nuevaposY] != '|') {
        posicionX = nuevaposX;
        posicionY = nuevaposY;
    }
}

// Funci�n principal del juego
void juego() {
    char resp;
    char input;
    bool indicador = true; // Controla si se sigue jugando

    while (indicador) {
        // Reinicia la posici�n del jugador
        posicionX = 9;
        posicionY = 0;

        while (true) {
            printlaber(); // Imprime el laberinto
            cout << "Mueve el jugador (W/A/S/D): ";
            cin >> input;

            movePlayer(input); // Actualiza la posici�n del jugador

            // Verifica si el jugador llega a la meta
            if (laber[posicionX][posicionY] == 'E') {
                cout << "�Ganaste!\n";
                cout << "�Quieres jugar de nuevo? (S/N): ";
                cin >> resp;

                // Verifica la respuesta del jugador
                if (resp == 'N' || resp == 'n') {
                    indicador = false; // Finaliza el bucle principal
                    cout << "Gracias por jugar :)" << endl;
                }
                break; // Sal del bucle interno para reiniciar o terminar
            }
        }
    }
}

// Funci�n para calcular el puntaje basado en el tiempo
void puntaje(int jugadorIndex) {
    // Guardamos el tiempo de inicio
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    juego();  // Ejecuta el juego

    // Guardamos el tiempo de finalizaci�n
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();

    // Calculamos la diferencia entre los dos tiempos
    chrono::duration<double> duration = end - start;

    // Asignamos el puntaje seg�n el tiempo
    if (duration.count() < 10) {
        jugadores[jugadorIndex].puntaje = 20;
    } else if (duration.count() < 20) {
        jugadores[jugadorIndex].puntaje = 15;
    } else {
        jugadores[jugadorIndex].puntaje = 10;
    }
}

int main() {
    int opcion;
    
    do {
        cout << "Juego Del Laberinto" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Agregar nombres" << endl;
        cout << "3. Mostrar Puntajes" << endl;
        cout << "4. Creditos del Juego" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                for (int i = 0; i < numJugadores; i++) {
                    cout << "Iniciando juego para " << jugadores[i].nombre << endl;
                    puntaje(i);  // Calcular y guardar el puntaje para cada jugador
                }
                break;

            case 2:
                agregarJugador();  // Agregar un nuevo jugador
                break;

            case 3:
                mostrarPuntajes();  // Mostrar puntajes de los jugadores
                break;

            case 4:
                cout << "Creditos del Juego" << endl;
                cout << "Juego Hecho Por:" << endl;
                cout << "Mateo Aimaca�a" << endl;
                cout << "Galarraga Andres" << endl;
                break;

            case 5:
                return 0; // Salir del programa

            default:
                cout << "Opci�n no v�lida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);

    return 0;
}

