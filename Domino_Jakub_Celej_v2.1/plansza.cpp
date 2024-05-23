#include <stdio.h>

#include "plansza.h"

plansza::plansza() {
	kamienNaPlanszy = NULL;
	nast = NULL;
}

plansza::plansza(kamien* k) {
	kamienNaPlanszy = k;
	nast = NULL;
}

plansza::~plansza() {
	delete nast;
}

kamien* plansza::getKamienNaPlanszy() {
	return kamienNaPlanszy;
}

void dodajDoPlanszy(plansza** p, kamien* k, int LewoPrawo, int obrot) {
	plansza* nowy = new plansza(k);
	if (*p == NULL) {
		*p = nowy;
	}
	else {
		if (obrot == 0) {
			k->setObrot(0);
		}
		else {
			k->setObrot(1);
		}
		if (LewoPrawo == 0) {	//z lewej
			nowy->nast = *p;
			*p = nowy;
		}
		else {	//	z prawej
			plansza* wsk = *p;
			while (wsk->nast != NULL) {
				wsk = wsk->nast;
			}
			wsk->nast = nowy;
		}
	}
	k->setCzyNaPlanszy(1);
}

void wypiszPlansze(plansza** head) {
	plansza* wsk = *head;
	while (wsk != NULL) {
		kamien* temp = wsk->getKamienNaPlanszy();
		temp->wypisz();
		wsk = wsk->nast;
	}
}