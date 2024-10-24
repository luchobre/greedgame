#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cctype>
#include <algorithm>
#include <numeric>
#include "funciones.h"
using namespace std;

int menu()
{
    int opc;
    do
    {
        cout << "                              GREED                    " << endl;
        cout << "                    _______________________________                    " << endl;
        cout << "                              1- 1 JUGADOR                    " << endl;
        cout << "                              2- 2 JUGADORES                    " << endl;
        cout << "                              3- ESTADISTICAS                    " << endl;
        cout << "                              4- CREDITOS                    " << endl;
        cout << "                    _______________________________                    " << endl;
        cout << "                              0- SALIR                    " << endl;
        cin >> opc;

        if (opc >= 0 && opc <= 4)
        {
            return opc;
        }
        else
        {
            cout << "Opción no válida. Intente nuevamente." << endl;
        }

    }
    while (opc != 0);
}

//Logica de juego 1 jugador

void onePlayer()
{
    string nombreJugador1;
    cout << endl << "Ingrese el nombre del Jugador N 1: ";
    cin >> nombreJugador1;

    cout << endl << "Bienvenido " << nombreJugador1 << "! Mucha suerte!" << endl;

    int puntajeTotal = 0;

    for (int ronda = 1; ronda <= 3; ++ronda)
    {
        cout << endl << "               --------------- Ronda " << ronda << " ---------------               " << endl;
        puntajeTotal += jugarRonda();
        cout << "Puntaje total acumulado: " << puntajeTotal << endl;
    }

    cout << "Puntaje final de " << nombreJugador1 << ": " << puntajeTotal << endl;
}

//Logica de juego 2 jugadores

void twoPlayers()
{
    string nombreJugador1, nombreJugador2;

    cout << endl << "Ingrese el nombre del Jugador N 1: ";
    cin >> nombreJugador1;
    cout << endl << "Ingrese el nombre del Jugador N 2: ";
    cin >> nombreJugador2;

    cout << endl << "Bienvenidos " << nombreJugador1 << " y " << nombreJugador2 << "! Mucha suerte!" << endl;

    int puntajeTotal1 = 0, puntajeTotal2 = 0;

    for (int ronda = 1; ronda <= 3; ++ronda)
    {
        cout << endl << "               --------------- Ronda " << ronda << " ---------------               " << endl;

        cout << "Turno de " << nombreJugador1 << endl;
        puntajeTotal1 += jugarRonda();
        cout << "Puntaje total acumulado de " << nombreJugador1 << ": " << puntajeTotal1 << endl;

        cout << "Turno de " << nombreJugador2 << endl;
        puntajeTotal2 += jugarRonda();
        cout << "Puntaje total acumulado de " << nombreJugador2 << ": " << puntajeTotal2 << endl;
    }

    cout << "Puntaje final de " << nombreJugador1 << ": " << puntajeTotal1 << endl;
    cout << "Puntaje final de " << nombreJugador2 << ": " << puntajeTotal2 << endl;

    if (puntajeTotal1 > puntajeTotal2)
    {
        cout << nombreJugador1 << " gana el juego!" << endl;
    }
    else if (puntajeTotal2 > puntajeTotal1)
    {
        cout << nombreJugador2 << " gana el juego!" << endl;
    }
    else
    {
        cout << "Es un empate!" << endl;
    }
}

void creditos ()
{
    cout << endl << "Juego creado por el grupo N 12 de Programacion 1 para la UTN-Facultad Regional General Pacheco" << endl << endl;
    cout << "Maria Sol Collao Pichilingue"<< endl;
    cout << "Rodrigo Fernando Rimbau "    << endl ;
    cout << "Francisco Degui"             << endl  ;
    cout << "Luciano Matias Bregoli"       << endl  ;
}


//Funcion para tirar un dado
int tirarDado()
{
    return (rand() % 6) + 1;
}

//Funcion para mostrar los dados lanzados
void mostrarDados(const vector<int>& dados)
{
    for (int i = 0; i < dados.size(); ++i)
    {
        cout << "     Dado " << i + 1 << ": " << dados[i] << endl;
    }
}

//Funcion para jugar 1 ronda
int jugarRonda()
{
    //Inicializacion para los numeros aleatorios
    srand(static_cast<unsigned>(time(0)));

    //Creamos el vector para acumular los dados
    vector<int> dados(5);
    int blocker1 = tirarDado(), blocker2 = tirarDado();
    int totalPuntajeRonda = 0;
    char seguir = 'S';

    //Muestro los bloqueadores
    cout << "                    Bloqueadores: " << blocker1 << " y " << blocker2 << endl;

    //Mientras que se quiera seguir jugando y el vector de dados no este vacio asignar un nuevo valor a cada posicion del vector
    while (seguir == 'S' && !dados.empty())
    {
        for (int& dado : dados)
        {
            dado = tirarDado();
        }
        mostrarDados(dados);
        //Revisa todos los valores del vector desde el principio al final y verifica que la posicion actual sea igual a la primera posicion del vector
        bool todosIguales = all_of(dados.begin(), dados.end(), [&](int x)
        {
            return x == dados[0];
        });
        //Si todos los dados son iguales pero distintos que los bloqueadores, se duplica el puntaje
        if (todosIguales && dados[0] != blocker1 && dados[0] != blocker2)
        {
            cout << "Todos los dados son iguales! Se duplica su puntaje en esta tirada." << endl;
            totalPuntajeRonda += 2 * accumulate(dados.begin(), dados.end(), 0);
        }
        else
        {
            for (int i = 0; i < dados.size(); ++i)
            {
                //Verificar si los dados son distintos o iguales a los bloqueadores para dejarlos del vector o borrarlos
                if (dados[i] != blocker1 && dados[i] != blocker2)
                {
                    totalPuntajeRonda += dados[i];
                }
                else
                {
                    cout << "Dado bloqueado." << endl;
                    dados.erase(dados.begin() + i);
                    --i;
                }
            }
        }

        //Se suma el puntaje de la ronda
        cout << endl <<"Puntaje actual de la ronda: " << totalPuntajeRonda << endl <<endl;

        //Se verifica si el vector está o no vacio para continuar jugando o terminar la ronda.
        if (!dados.empty())
        {
            cout << "Deseas seguir tirando? (S/N): ";
            cin >> seguir;
            seguir = toupper(seguir);
            cout << endl;
        }
        else
        {
            cout << "No quedan dados para tirar, ronda terminada." << endl;
            break;
        }
    }

    //Si el vector está vacio el puntaje cambia a 0
    if (dados.empty())
    {
        cout << "Te quedaste sin dados, puntaje de esta ronda es 0." << endl;
        totalPuntajeRonda = 0;
    }

    return totalPuntajeRonda;
}


void options(int opc)
{
    switch (opc)
    {
    case 1:
        onePlayer();
        break;
    case 2:
        twoPlayers();
        break;
    case 3:
        cout << "Esta es la opcion 3 (Estadísticas)" << endl;
        break;
    case 4:
        creditos();
        break;
    case 0:
        cout << "Cerrando el juego..." << endl;
        break;
    default:
        cout << "Opción no válida" << endl;
    }
}
