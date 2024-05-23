#ifndef misc_h
#define misc_h

#include "gracz.h"
#include <iostream>

using namespace std;

#pragma warning(disable : 4996)

#define dlugoscNazwPlikow 50

void czysc();	//czysci bufor klawiatury

void cmdClear();	//"czysci" okno konsoli poprzez wypisanie stu '\n'

void stronaTytulowa();	//wypisuje strone tytulowa gry

int czyIstniejePlik(const char nazwaPliku[dlugoscNazwPlikow]);	//sprawdza, czy istnieje plik o podanej nazwie

void zapiszDoPliku(const char nazwaPliku[dlugoscNazwPlikow], int ktoWygral, int czyZBotem, char gracz1[dlugoscNicku], int wygrane1, int punkty1, char gracz2[dlugoscNicku], int wygrane2, int punkty2);
//dokonuje zapisu wyniku do pliku o podanej nazwie
//ktoWygral | 1 - wygral gracz 1; 2 - wygral gracz 2;
//czyZBotem | 1 - gra odbyla sie w trybie GraczVsKomputer; 2 - w trybie GraczVsGracz
//gracz1/gracz2 | nazwy graczy
//wygrane1/wygrane2 | liczba rund wygranych przez graczy
//punkty1/punkty2 | punkty graczy

#endif