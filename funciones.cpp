#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cctype>
#include <algorithm>
#include <numeric>
#include <windows.h>
#include "rlutil.h"
#include "funciones.h"
using namespace std;

int menu()
{
    int opc =1,y=0;
    rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
    rlutil::setColor(rlutil::WHITE);

    do
    {
        rlutil::cls();
        rlutil::hidecursor();

        rlutil::locate(60, 10);
        cout << "GREED" << endl <<endl;

        showItem("1 JUGADOR", 50, 12, y==0);
        showItem("2 JUGADORES", 50, 13, y==1);
        showItem("ESTADISTICAS", 50, 14, y==2);
        showItem("CREDITOS", 50, 15, y==3);
        showItem("SALIR", 50, 16, y==4);

        rlutil::locate(47, 12 + y);
        cout << (char)175 << endl;

        rlutil::locate(63, 12 + y);
        cout << (char)174 << endl;

        int key = rlutil::getkey();


        switch (key)
        {
        case 14:
            if(y>0)
            {
                y--;
                opc--;
            }
            break;
        case 15:
            if(y<4)
            {
                y++;
                opc++;
            }
            break;
        case 1:
            return opc;
            break;
        default:
            break;
        }
    }
    while(true);
}

//Logica para poner fondo de color a lo seleccionado en el menu

void showItem(const char* text, int posx, int posy, bool selected)
    {
        if(selected)
        {
            rlutil::setBackgroundColor(rlutil::BLUE);
        }
        else
        {
           rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
        }
        rlutil::locate(posx, posy);
        cout<<text<<endl;
        rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
    }

//Logica de juego 1 jugador

void onePlayer()
{
    string nombreJugador1;
    cout << endl << "Ingrese el nombre del Jugador N 1: ";
    cin >> nombreJugador1;

    cout << endl << "Bienvenido " << nombreJugador1 << "! Mucha suerte!" << endl;
    cout << "Presione cualquier tecla para lanzar los dados...";
    rlutil::anykey();

    int puntajeTotal = 0;

    for (int ronda = 1; ronda <= 3; ++ronda)
    {
        cout << endl << "               --------------- Ronda " << ronda << " ---------------               " << endl;
        puntajeTotal += jugarRonda();
        cout << "Puntaje total acumulado: " << puntajeTotal << endl;
    }
    PlaySound(TEXT("winner.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "Puntaje final de " << nombreJugador1 << ": " << puntajeTotal << endl;
    cout << "Presione cualquier tecla para regresar al menu principal...";
    rlutil::anykey();
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
    cout << "Presione cualquier tecla para lanzar los dados...";
    rlutil::anykey();

    int puntajeTotal1 = 0, puntajeTotal2 = 0;

    for (int ronda = 1; ronda <= 3; ++ronda)
    {
        cout << endl << "               --------------- Ronda " << ronda << " ---------------               " << endl;

        cout <<endl << "Turno de " << nombreJugador1 << endl;
        puntajeTotal1 += jugarRonda();
        cout << "Puntaje total acumulado de " << nombreJugador1 << ": " << puntajeTotal1 << endl;

        cout <<endl << "Turno de " << nombreJugador2 << endl;
        puntajeTotal2 += jugarRonda();
        cout << "Puntaje total acumulado de " << nombreJugador2 << ": " << puntajeTotal2 << endl;
    }

    cout << "Puntaje final de " << nombreJugador1 << ": " << puntajeTotal1 << endl;
    cout << "Puntaje final de " << nombreJugador2 << ": " << puntajeTotal2 << endl;

    if (puntajeTotal1 > puntajeTotal2)
    {
        PlaySound(TEXT("winner.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << nombreJugador1 << " gana el juego!" << endl;
    }
    else if (puntajeTotal2 > puntajeTotal1)
    {
        PlaySound(TEXT("winner.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << nombreJugador2 << " gana el juego!" << endl;
    }
    else
    {
        cout << "Es un empate!" << endl;
    }
    cout << "Presione cualquier tecla para regresar al menu principal...";
    rlutil::anykey();
}

void creditos ()
{
    cout << endl << "Juego creado por el grupo N 21 de Programacion 1 para la UTN-Facultad Regional General Pacheco" << endl << endl;
    cout << "Maria Sol Collao Pichilingue"<< endl;
    cout << "Rodrigo Fernando Rimbau "    << endl ;
    cout << "Francisco Degui"             << endl  ;
    cout << "Luciano Matias Bregoli"       << endl  ;
}


//Funcion para tirar un dado                    S
int tirarDado()
{
    PlaySound(TEXT("tirardados.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
        rlutil::locate(50, 20);
        onePlayer();
        break;
    case 2:
        rlutil::locate(50, 20);
        twoPlayers();
        break;
    case 3:
        rlutil::locate(50, 20);
        cout << "Esta es la opcion 3 (Estadísticas)" << endl;
        break;
    case 4:
        rlutil::locate(50, 20);
        creditos();
        rlutil::anykey();
        break;
    case 5:
        rlutil::locate(50, 20);
        cout << "Cerrando el juego..." << endl;
        break;
    default:
        rlutil::locate(50, 20);
        cout << "Opción no válida" << endl;
    }
}
