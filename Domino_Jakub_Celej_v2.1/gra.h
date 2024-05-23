#ifndef gra_h
#define gra_h

#include "gracz.h"

int runda(gracz* CZ1, gracz* CZ2, const char* nick1, const char* nick2, int ktoZaczyna);	//jedna runda domino

void singleplayer();	//tryb gracz vs. komputer

void multiplayer();	//tryb gracz vs. gracz

#endif