#include "bot.h"
#include "gracz.h"
#include "misc.h"

#include <stdio.h>
#include <stdlib.h>

bot::bot() : gracz() {
	strcpy(nick, "BOT-Domino");
};

bot::bot(int id, kamienieGracza** h) : gracz(id, h) {
	strcpy(nick, "BOT-Domino");
};

char* bot::getNick() {
	return nick;
}


int bot::wykonajRuch(plansza** p, kamien** pula, gracz* przeciwnik) {
	cmdClear();
	kamienieGracza* kG = getKamienieGraczaGlowa();
	kamienieGracza* wsk = kG;
	kamien* k = NULL;
	int x = 0;
	//BOT sprawdza czy ma pasujacy kamien
	int obroty = 0;

	while (czyPosiadaPasujacyKamien(p) == 0 && czyJestNieuzytyKamien(pula) == 1) {
		obroty++;
		k = losujNowy(pula);
		if (k == NULL) {
			break;
		}
		dodajKamien(k);
	}

	if ((czyPosiadaPasujacyKamien(p) == 0)) {
		//jesli nie - pomija ture
		wypiszKamienieGracza(p);
		printf("\nBot nie posiada pasujacych kamieni. ");
		system("pause");
		return -1;
	}
	else {
		//jesli tak - dodaje pierwszy pasujacy
		wsk = kG;
		k = NULL;
		while (wsk != NULL) {
			if (wsk->czyPasujeZLewej(p) != 0) {
				k = wsk->getKamienReka();
				if (k->getCzyNaPlanszy() == 0) {
					break;
				}
			}
			else if (wsk->czyPasujeZPrawej(p) != 0) {
				k = wsk->getKamienReka();
				if (k->getCzyNaPlanszy() == 0) {
					break;
				}
			}
			wsk = wsk->nast;
		}
		if (wsk->czyPasujeZLewej(p) != 0 && wsk->czyPasujeZPrawej(p) != 0) {
			//dodaje tylko z lewej
			if (wsk->czyPasujeZLewej(p) == 1) {
				dodajDoPlanszy(p, k, 0, 1);
			}
			else {
				dodajDoPlanszy(p, k, 0, 0);
			}
		}
		else if (wsk->czyPasujeZLewej(p) != 0) {
			//dodaje tylko z lewej
			if (wsk->czyPasujeZLewej(p) == 1) {
				dodajDoPlanszy(p, k, 0, 1);
			}
			else {
				dodajDoPlanszy(p, k, 0, 0);
			}
		}
		else if (wsk->czyPasujeZPrawej(p) != 0) {
			//dodaje tylko z prawej
			if (wsk->czyPasujeZPrawej(p) == 1) {
				dodajDoPlanszy(p, k, 1, 0);
			}
			else {
				dodajDoPlanszy(p, k, 1, 1);
			}
		}
		k->setCzyNaPlanszy(1);
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
	interfejs(p, this, przeciwnik, pula);
	printf("Bot wykonal ruch. Uzyl kamienia: ");
	k->wypisz();
	printf(". ");
	system("pause");
	return 1;
}