#include "gracz.h"
#include "misc.h"
#include "kamien.h"

#include <stdio.h>
#include <stdlib.h>

void gracz::setKamienieGraczaGlowa(kamienieGracza* h) {
	kamienieGraczaGlowa = h;
}

int gracz::getID() {
	return id;
}

int gracz::sumaOczekWRece() {
	int suma = 0;
	kamienieGracza* wsk = kamienieGraczaGlowa;
	while (wsk != NULL) {
		kamien* k = wsk->getKamienReka();
		if (k->getCzyNaPlanszy() == 0) {
			suma = suma + k->getDol() + k->getGora();
		}
		wsk = wsk->nast;
	}
	return suma;
}

kamienieGracza* gracz::getKamienieGraczaGlowa() {
	return kamienieGraczaGlowa;
}

int gracz::liczbaKamieniGracza() {
	kamienieGracza* wsk = kamienieGraczaGlowa;
	int liczba = 0;
	while (wsk != NULL) {
		kamien* aktualny = wsk->getKamienReka();
		if (aktualny->getCzyNaPlanszy() == 0) {
			liczba++;
		}
		wsk = wsk->nast;
	}

	return liczba;
}

gracz::gracz() : id(-1), punkty(0) {
	strcpy(nick, "NazwaDomyslna");
	kamienieGraczaGlowa = NULL;
	nast = NULL;
}

gracz::gracz(int ID, kamienieGracza** head) : id(ID), punkty(0) {
	strcpy(nick, "NazwaDomyslna");
	kamienieGraczaGlowa = *head;
	nast = NULL;
}

gracz::~gracz() {
	delete nast;
}
char* gracz::getNick() {
	return nick;
}

int gracz::getPunkty() {
	return punkty;
}

void gracz::setPunkty(int x) {
	punkty = x;
}

void gracz::dodajPunkty(int x) {
	punkty += x;
}

void gracz::ukryjKamien(int nr) {
	kamienieGracza* wsk = kamienieGraczaGlowa;
	while (wsk != NULL) {
		if (wsk->getNrKamienia() == nr) {
			wsk->setNrKamienia(-1);
			break;
		}
		wsk = wsk->nast;
	}
	wsk = kamienieGraczaGlowa;
	int i = -1;
	while (wsk != NULL) {
		if (wsk->getNrKamienia() != -1) {
			i++;
			wsk->setNrKamienia(i);
		}
		wsk = wsk->nast;
	}
}

void gracz::dodajKamien(kamien* k) {
	int ktory = 1;
	kamienieGracza* wsk = kamienieGraczaGlowa;
	while (wsk->nast != NULL) {
		ktory++;
		wsk = wsk->nast;
	}
	kamienieGracza* nowy = new kamienieGracza(k, ktory);
	if (kamienieGraczaGlowa == NULL) {
		kamienieGraczaGlowa = nowy;
	}
	else {

		ktory++;
		wsk->nast = nowy;
	}


	k->setNrGracza(id);
}

void interfejs(plansza** p, gracz* grajacy, gracz* przeciw, kamien** pulaK) {
	kamien* wskK = *pulaK;
	int ileWPuli = 0;
	while (wskK != NULL) {
		if (wskK->getCzyNaPlanszy() == 0 && wskK->getNrGracza() == -1) {
			ileWPuli++;
		}
		wskK = wskK->nast;
	}
	printf("Liczba kamieni w puli: %d\n", ileWPuli);
	printf("%s - Punkty: %d - Kamienie:", przeciw->getNick(), przeciw->getPunkty());
	int x = przeciw->liczbaKamieniGracza();
	for (int i = 0; i < x; i++) {
		printf(" [?|?]");
	}
	putchar('\n');

	for (int i = 0; i < ileKamieni * 5; i++) {
		printf("#");
	}
	printf("\n\n\n\n\n");
	wypiszPlansze(p);
	printf("\n\n\n\n\n");
	for (int i = 0; i < ileKamieni * 5; i++) {
		printf("#");
	}

	printf("\n%s - Punkty: %d\n", grajacy->getNick(), grajacy->getPunkty());
	putchar('\n');
}

void gracz::wypiszKamienieGracza(plansza** p) {
	kamienieGracza* wsk = kamienieGraczaGlowa;
	kamien* aktualny = NULL;
	while (wsk != NULL) {
		int nr = wsk->getNrKamienia();
		aktualny = wsk->getKamienReka();
		if (aktualny->getCzyNaPlanszy() == 0) {

			printf("%d", nr);
			if (wsk->czyPasujeZLewej(p) != 0 || wsk->czyPasujeZPrawej(p) != 0) {
				putchar('*');
			}
			putchar('.');
			aktualny->wypisz();
			putchar(' ');

		}
		wsk = wsk->nast;
	}
}



int gracz::czyPosiadaPasujacyKamien(plansza** p) {
	kamienieGracza* h = kamienieGraczaGlowa;
	kamienieGracza* wsk = kamienieGraczaGlowa;
	while (wsk != NULL) {
		kamien* aktualny = wsk->getKamienReka();
		if ((wsk->czyPasujeZLewej(p) != 0 || wsk->czyPasujeZPrawej(p) != 0) && aktualny->getCzyNaPlanszy() == 0) {
			return 1;
		}
		wsk = wsk->nast;
	}
	return 0;
}

int gracz::wykonajRuch(plansza** p, kamien** pula, gracz* przeciwnik) {
	cmdClear();
	printf("Ruch gracza: %s Przeciwnik: %s\n\n", getNick(), przeciwnik->getNick());
	printf("- - - - -\n\n");
	interfejs(p, this, przeciwnik, pula);
	printf("1. Zakoncz; 2. Wykonaj ruch;		Twoj wybor: ");
	int wybor = 0;
	while (scanf_s("%d", &wybor) != 1 || getchar() != '\n' || (wybor != 1 && wybor != 2)) {
		printf("\nPodano bledne dane, popraw: ");
		czysc();
	}
	if (wybor == 1) {
		return 0;
	}
	else {

		kamien* k = NULL;
		int obroty = 0;
		while (czyPosiadaPasujacyKamien(p) == 0 && czyJestNieuzytyKamien(pula) == 1) {
			obroty++;
			k = losujNowy(pula);
			if (k == NULL) {
				break;
			}
			dodajKamien(k);
		}

		kamienieGracza* kG = kamienieGraczaGlowa;
		kamienieGracza* wsk = kG;
		int x = 0;
		while (wsk != NULL) {
			kamien* tempK = wsk->getKamienReka();
			if (tempK->getCzyNaPlanszy() == 0) {
				wsk->setNrKamienia(x);
				x++;
			}
			else if (tempK->getCzyNaPlanszy() == 1) {
				wsk->setNrKamienia(-1);
			}
			wsk = wsk->nast;
		}
		cmdClear();
		interfejs(p, this, przeciwnik, pula);

		printf("\n");
		if ((czyPosiadaPasujacyKamien(p) == 0)) {
			wypiszKamienieGracza(p);
			printf("\nNie posiadasz pasujacych kamieni. Wcisnij \"Enter\", aby kontynuowac...");
			system("pause");
			return -1;
		}
		else {
			int ktory = 0;
			wsk = NULL;
			kamien* k = NULL;

			wypiszKamienieGracza(p);
			do {
				printf("\n\nKtory kamien dodac do planszy: ");
				ktory = 0;

				int ileKamieniG = liczbaKamieniGracza();
				while (scanf_s("%d", &ktory) != 1 || getchar() != '\n' || (ktory < 0 || ktory >= ileKamieniG)) {
					printf("\nPodano bledne dane, popraw: ");
					czysc();
				}

				wsk = kG;
				while (wsk != NULL) {
					if (wsk->getNrKamienia() == ktory) {

						break;
					}
					wsk = wsk->nast;
				}
				k = wsk->getKamienReka();
			} while (wsk->czyPasujeZLewej(p) == 0 && wsk->czyPasujeZPrawej(p) == 0);
			cmdClear();
			interfejs(p, this, przeciwnik, pula);

			putchar('\n');
			k->wypisz();
			if (wsk->czyPasujeZLewej(p) != 0 && wsk->czyPasujeZPrawej(p) != 0) {
				//uzytkownik wybiera czy dodac z lewej czy z prawej
				printf("1. Z lewej; 2. Z prawej;	Z ktorej strony dodac kamien?: ");
				int LewoPrawo = 0;
				while (scanf_s("%d", &LewoPrawo) != 1 || getchar() != '\n' || (LewoPrawo != 1 && LewoPrawo != 2)) {
					printf("\nPodano bledne dane, popraw: ");
					czysc();
				}
				if (LewoPrawo == 1) {
					if (wsk->czyPasujeZLewej(p) == 1) {
						dodajDoPlanszy(p, k, 0, 1);
					}
					else {
						dodajDoPlanszy(p, k, 0, 0);
					}
				}
				else if (LewoPrawo == 2) {
					if (wsk->czyPasujeZPrawej(p) == 1) {
						dodajDoPlanszy(p, k, 1, 0);
					}
					else {
						dodajDoPlanszy(p, k, 1, 1);
					}
				}

			}
			else if (wsk->czyPasujeZLewej(p) != 0 && wsk->czyPasujeZPrawej(p) == 0) {
				//dodaje tylko z lewej
				if (wsk->czyPasujeZLewej(p) == 1) {
					dodajDoPlanszy(p, k, 0, 1);
				}
				else {
					dodajDoPlanszy(p, k, 0, 0);
				}
			}
			else if (wsk->czyPasujeZLewej(p) == 0 && wsk->czyPasujeZPrawej(p) != 0) {
				//dodaje tylko z prawej
				if (wsk->czyPasujeZPrawej(p) == 1) {
					dodajDoPlanszy(p, k, 1, 0);
				}
				else {
					dodajDoPlanszy(p, k, 1, 1);
				}
			}
			wsk = kG;
			int x = 0;
			while (wsk != NULL) {
				kamien* tempK = wsk->getKamienReka();
				if (tempK->getCzyNaPlanszy() == 0) {
					wsk->setNrKamienia(x);
					x++;
				}
				else if (tempK->getCzyNaPlanszy() == 1) {
					wsk->setNrKamienia(-1);
				}
				wsk = wsk->nast;
			}

			plansza* pierwszy = *p;
			plansza* ostatni = *p;
			while (ostatni->nast != NULL) {
				ostatni = ostatni->nast;
			}
			kamien* pierwszyKamien = pierwszy->getKamienNaPlanszy();
			kamien* ostatniKamien = ostatni->getKamienNaPlanszy();
			int wartoscPierwszego, wartoscOstatniego;


			//obliczanie wartosci pierwszego kamienia na planszy
			if (pierwszyKamien->czyDubel() == 1) {
				wartoscPierwszego = pierwszyKamien->getGora() + pierwszyKamien->getDol();
			}
			else {
				if (pierwszyKamien->getObrot() == 0) {
					wartoscPierwszego = pierwszyKamien->getGora();
				}
				else {
					wartoscPierwszego = pierwszyKamien->getDol();
				}
			}
			//obliczanie wartosci ostatniego kamienia na planszy
			if (ostatniKamien->czyDubel() == 1) {
				wartoscOstatniego = ostatniKamien->getGora() + ostatniKamien->getDol();
			}
			else {
				if (ostatniKamien->getObrot() == 0) {
					wartoscOstatniego = ostatniKamien->getDol();
				}
				else {
					wartoscOstatniego = ostatniKamien->getGora();
				}
			}
			//sprawdz czy suma tych wartosci jest podzielna przez 5, jesli tak dodaj sume do punktow
			int suma = wartoscOstatniego + wartoscPierwszego;
			if (suma % 5 == 0) {
				dodajPunkty(suma);
			}

		}
	}
	return 1;
}