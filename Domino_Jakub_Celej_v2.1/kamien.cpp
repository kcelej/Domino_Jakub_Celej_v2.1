#include <stdio.h>
#include <stdlib.h>

#include "kamien.h"

kamien::kamien() : id(0), gora(0), dol(0), obrotLewoPrawo(0), nrGracza(-1), czyNaPlanszy(0) {
	nast = NULL;
}

kamien::kamien(int ID, int G, int D, int obrot) : id(ID), gora(G), dol(D), obrotLewoPrawo(obrot), nrGracza(-1), czyNaPlanszy(0) {
	nast = NULL;
}

kamien::~kamien() {
	delete nast;
}



int kamien::getID() {
	return id;
}

int kamien::getGora() {
	return gora;
}

int kamien::getDol() {
	return dol;
}

int kamien::getObrot() {
	return obrotLewoPrawo;
}

int kamien::getNrGracza() {
	return nrGracza;
}

int kamien::getCzyNaPlanszy() {
	return czyNaPlanszy;
}

void kamien::setObrot(int o) {
	obrotLewoPrawo = o;
}

void kamien::setNrGracza(int nr) {
	nrGracza = nr;
}

void kamien::setCzyNaPlanszy(int czy) {
	czyNaPlanszy = czy;
}

int kamien::czyDubel() {
	if (gora == dol) {
		return 1;
	}
	else {
		return 0;
	}
}



void kamien::wypisz() {
	char lewo = 0, prawo = 0;
	if (getObrot() == 0) {
		//kamien obrocony w lewo (G|D)
		lewo = getGora();
		prawo = getDol();
	}
	else {
		//kamien obrocony w prawo (D|G)
		lewo = getDol();
		prawo = getGora();
	}
	printf("[%d|%d]", lewo, prawo);
}

int czyJestNieuzytyKamien(kamien** k) {
	kamien* wsk = *k;
	while (wsk != NULL) {
		if (wsk->getCzyNaPlanszy() == 0 && wsk->getNrGracza() == -1) {
			return 1;
		}
		wsk = wsk->nast;
	}
	return 0;
}

kamien* losujNowy(kamien** k) {
	kamien* wsk = *k;
	int x = (rand() % ileKamieni), obrotPoLiscie = 0;
	while (wsk != NULL) {
		if (x == wsk->getID()) {
			if (wsk->getNrGracza() == -1 && wsk->getCzyNaPlanszy() == 0) {
				return wsk;
			}
			else {
				x++;
			}
		}
		if (x == (ileKamieni - 1) && obrotPoLiscie == 0) {
			x = 0;
			wsk = *k;
			obrotPoLiscie = 1;
			continue;
		}
		else if (x == (ileKamieni - 1) && obrotPoLiscie == 1) {
			break;
		}
		wsk = wsk->nast;
	}
	return NULL;
}

void stworzPuleKamieni(kamien** head) {
	kamien* wsk = NULL;
	int ktory = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = i; j >= 0; j--) {
			kamien* nowy = new kamien(ktory, i, j, 0);
			if (*head == NULL) {
				*head = nowy;
				wsk = nowy;
			}
			else {
				kamien* now = *head;
				while (now->nast != NULL) {
					now = now->nast;
				}
				now->nast = nowy;
				wsk = nowy;
			}
			ktory++;
		}
	}
}

int ileNiewykorzystanychKamieni(kamien** head) {
	kamien* wsk = *head;
	int ile = 0;
	while (wsk != NULL) {
		if (wsk->getCzyNaPlanszy() == 0 || wsk->getNrGracza() != -1) {
			ile++;
		}
		wsk = wsk->nast;
	}
	return ile;
}

void wypiszPule(kamien** head) {
	kamien* wsk = *head;
	while (wsk != NULL) {
		if (wsk->getCzyNaPlanszy() == 0 && wsk->getNrGracza() == -1) {
			wsk->wypisz();
		}
		wsk = wsk->nast;
	}
}