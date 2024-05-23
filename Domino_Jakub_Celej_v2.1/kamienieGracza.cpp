#include "kamienieGracza.h"

#include <stdio.h>

kamienieGracza::kamienieGracza() : nrKamienia(-1) {
	kamienReka = NULL;
	nast = NULL;
}

kamienieGracza::kamienieGracza(kamien* dodaj, int nr) : nrKamienia(nr) {
	kamienReka = dodaj;
	nast = NULL;
}

kamienieGracza::~kamienieGracza() {
	delete nast;
}

int kamienieGracza::getNrKamienia() {
	return nrKamienia;
}

kamien* kamienieGracza::getKamienReka() {
	return kamienReka;
}

void kamienieGracza::setNrKamienia(int x) {
	nrKamienia = x;
}

int kamienieGracza::czyPasujeZLewej(plansza** head) {
	plansza* wsk = *head;
	kamien* lewySkrajny = wsk->getKamienNaPlanszy();


	int goraKamienReka = kamienReka->getGora();
	int dolKamienReka = kamienReka->getDol();

	if (lewySkrajny->getObrot() == 0) {
		int lewyGora = lewySkrajny->getGora();
		if (lewyGora == goraKamienReka) {
			return 1;	//gora kamienia pasuje do lewej (kamien w rotacji 1)
		}
		else if (lewyGora == dolKamienReka) {
			return 2;	//dol kamienia pasuje do lewej (kamien w rotacji 0)
		}
	}
	else if (lewySkrajny->getObrot() == 1) {
		int lewyDol = lewySkrajny->getDol();
		if (lewyDol == goraKamienReka) {
			return 1;	//gora kamienia pasuje do lewej (kamien w rotacji 1)
		}
		else if (lewyDol == dolKamienReka) {
			return 2;	//dol kamienia pasuje do lewej (kamien w rotacji 0)
		}
	}
	return 0;	//nie pasuje nigdzie

}


int kamienieGracza::czyPasujeZPrawej(plansza** head) {
	plansza* wsk = *head;
	while (wsk->nast != NULL) {
		wsk = wsk->nast;
	}

	kamien* prawySkrajny = wsk->getKamienNaPlanszy();

	int goraKamienReka = kamienReka->getGora();
	int dolKamienReka = kamienReka->getDol();

	if (prawySkrajny->getObrot() == 1) {
		int prawyGora = prawySkrajny->getGora();
		if (prawyGora == goraKamienReka) {
			return 1;	//gora kamienia pasuje do prawej (kamien w rotacji 0)
		}
		else if (prawyGora == dolKamienReka) {
			return 2;	//dol kamienia pasuje do prawej (kamien w rotacji 1)
		}
	}
	else if (prawySkrajny->getObrot() == 0) {
		int prawyDol = prawySkrajny->getDol();
		if (prawyDol == goraKamienReka) {
			return 1;	//gora kamienia pasuje do prawej (kamien w rotacji 0)
		}
		else if (prawyDol == dolKamienReka) {
			return 2;	//dol kamienia pasuje do prawej (kamien w rotacji 1)
		}
	}
	return 0;	//nie pasuje nigdzie

}