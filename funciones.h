#pragma once
#include <iostream>
#include <vector>
using namespace std;

int tirarDado();
void mostrarDados(const vector<int>& dados);
int jugarRonda();
void onePlayer();
void twoPlayers();
int menu();
void options(int opc);
void showItem(const char* text, int posx, int posy, bool selected);
