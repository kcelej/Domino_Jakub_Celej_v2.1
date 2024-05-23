#include "gra.h"
#include "misc.h"
#include "czlowiek.h"
#include "bot.h"

#include <stdio.h>
#include <stdlib.h>

int runda(gracz* CZ1, gracz* CZ2, const char* nick1, const char* nick2, int ktoZaczyna) {
	kamien* pulaKamieni = NULL;
	stworzPuleKamieni(&pulaKamieni);

	kamien* wstepneDodanie = losujNowy(&pulaKamieni);
	kamienieGracza* KG1 = new kamienieGracza(wstepneDodanie, 0);
	wstepneDodanie->setNrGracza(0);
	CZ1->setKamienieGraczaGlowa(KG1);

	wstepneDodanie = losujNowy(&pulaKamieni);
	kamienieGracza* KG2 = new kamienieGracza(wstepneDodanie, 0);
	wstepneDodanie->setNrGracza(1);
	CZ2->setKamienieGraczaGlowa(KG2);

	wstepneDodanie = losujNowy(&pulaKamieni);
	plansza* planszaGry = new plansza(wstepneDodanie);
	wstepneDodanie->setCzyNaPlanszy(1);
	wstepneDodanie->setNrGracza(-2);

	for (int i = 0; i < 6; i++) {
		CZ1->dodajKamien(losujNowy(&pulaKamieni));
		CZ2->dodajKamien(losujNowy(&pulaKamieni));
	}
	int wyborGracza1 = -2;
	int wyborGracza2 = -2;
	int tura = 1;
	if (ktoZaczyna == 1) {
		tura = 0;
	}
	else {
		tura = 1;
	}
	int stanGry = -1; //-1 = gra w toku; 0 = gra przerwana; 1 = wygral gracz nr 1; 2 = wygral gracz nr 2;
	do {
		cmdClear();
		if (tura % 2 == 0) {
			printf("Ruch gracza: %s", CZ1->getNick());
			interfejs(&planszaGry, CZ1, CZ2, &pulaKamieni);
			wyborGracza1 = CZ1->wykonajRuch(&planszaGry, &pulaKamieni, CZ2);
			if (CZ1->liczbaKamieniGracza() == 0) {
				int x = CZ2->sumaOczekWRece() % 5;
				int dodaj = 0;
				if (x != 0) {
					dodaj = CZ2->sumaOczekWRece() - x + 5;
				}
				CZ1->dodajPunkty(dodaj);
				stanGry = 1;
			}
			else if (CZ1->getPunkty() >= 100) {
				stanGry = 1;
			}
		}
		else {
			printf("Ruch gracza: %s", CZ2->getNick());
			interfejs(&planszaGry, CZ1, CZ2, &pulaKamieni);
			wyborGracza2 = CZ2->wykonajRuch(&planszaGry, &pulaKamieni, CZ1);
			if (CZ2->liczbaKamieniGracza() == 0) {
				int x = CZ1->sumaOczekWRece() % 5;
				int dodaj = 0;
				if (x != 0) {
					dodaj = CZ1->sumaOczekWRece() - x + 5;
				}
				CZ2->dodajPunkty(dodaj);
				stanGry = 2;
			}
			else if (CZ2->getPunkty() >= 100) {
				stanGry = 2;
			}
		}
		tura++;
		if (wyborGracza1 == 0 || wyborGracza2 == 0) {
			//ktos wybierze zakoncz
			stanGry = 0;
		}
		else if (wyborGracza1 == -1 && wyborGracza2 == -1) {
			//wygrywa ten ktory ma mniejsza sume oczek niewykorzystanych kamieni
			int ilePunktow = 0, x = 0;
			if (CZ1->sumaOczekWRece() < CZ2->sumaOczekWRece()) {
				ilePunktow = CZ2->sumaOczekWRece() - CZ1->sumaOczekWRece();
				if (ilePunktow < 0) {
					ilePunktow = 5;
				}
				x = ilePunktow % 5;
				if (x != 0) {
					ilePunktow = ilePunktow - x + 5;
				}
				CZ1->dodajPunkty(ilePunktow);
				stanGry = 1;
			}
			else {
				ilePunktow = CZ1->sumaOczekWRece() - CZ2->sumaOczekWRece();
				if (ilePunktow < 0) {
					ilePunktow = 5;
				}
				x = ilePunktow % 5;
				if (x != 0) {
					ilePunktow = ilePunktow - x + 5;
				}
				CZ2->dodajPunkty(ilePunktow);
				stanGry = 2;
			}
			break;
		}

	} while (stanGry == -1);
	cmdClear();
	interfejs(&planszaGry, CZ1, CZ2, &pulaKamieni);
	if (stanGry == 1) {
		printf("\n----------------------------------\n");
		printf("\n\nRunde wygral gracz: %s\n\n", CZ1->getNick());
		printf("\n----------------------------------\n");
		return 1;
	}
	else if (stanGry == 2) {
		printf("\n----------------------------------\n");
		printf("\n\nRunde wygral gracz: %s\n\n", CZ2->getNick());
		printf("\n----------------------------------\n");
		return 2;
	}
	else {
		printf("\n-----------------------------------------------\n");
		printf("\n\nRunde przerwano. Wyniki nie zostana zapisane.\n\n");
		printf("\n-----------------------------------------------\n");
		return 0;
	}

	delete pulaKamieni;
	delete KG1;
	delete KG2;
}

void singleplayer() {
	printf("\nNazwa gracza:\n");
	char N1[dlugoscNicku];
	while (scanf_s("%s", &N1, dlugoscNicku) != 1 || getchar() != '\n') {
		printf("\nPodano bledne dane, popraw: ");
		czysc();
	}


	kamienieGracza* temp = new kamienieGracza();
	czlowiek* G1 = new czlowiek(N1, 0, &temp);

	bot* B1 = new bot(1, &temp);

	int wygraneGracza1 = 0, wygraneGracza2 = 0;
	int x = -1;
	int czyZakonczyc = 1;
	int ktoPierwszy = 1;
	do {
		x = runda(G1, B1, N1, B1->getNick(), ktoPierwszy);
		printf("\nRunda zakonczona. ");
		system("pause");
		cmdClear();
		if (x == 1) {
			wygraneGracza1++;
			ktoPierwszy = 1;
		}
		else if (x == 2) {
			wygraneGracza2++;
			ktoPierwszy = 2;
		}
		if (G1->getPunkty() < 100 && B1->getPunkty() < 100) {
			printf("\n############################\n");
			printf("Postep gry:\n\n");
			printf("%s:\n", G1->getNick());
			printf("Punkty: %d\n", G1->getPunkty());
			printf("Wygrane rundy: %d\n\n", wygraneGracza1);
			printf("%s:\n", B1->getNick());
			printf("Punkty: %d\n", B1->getPunkty());
			printf("Wygrane rundy: %d\n\n", wygraneGracza2);
			printf("\n############################\n");
			system("pause");
		}
		else if (G1->getPunkty() >= 100) {
			ktoPierwszy = 0;
			printf("\n############################\n");
			printf("############################\n");
			printf("\nGRE WYGRAL: %s\n", G1->getNick());
			printf("\n############################");
			printf("\n############################\n");
			zapiszDoPliku("wynikiDomino.txt", 1, 1, G1->getNick(), wygraneGracza1, G1->getPunkty(), B1->getNick(), wygraneGracza2, B1->getPunkty());
			system("pause");
		}
		else {
			ktoPierwszy = 1;
			printf("\n############################\n");
			printf("############################\n");
			printf("\nGRE WYGRAL: %s\n", B1->getNick());
			printf("\n############################");
			printf("\n############################\n");
			zapiszDoPliku("wynikiDomino.txt", 2, 1, G1->getNick(), wygraneGracza1, G1->getPunkty(), B1->getNick(), wygraneGracza2, B1->getPunkty());
			system("pause");
		}
		cmdClear();
		if ((G1->getPunkty() < 100 && B1->getPunkty() < 100) && x != 0) {
			printf("\n- 1 - TAK");
			printf("\n- 0 - NIE");
			printf("\nCzy chcesz kontynuowac?:\n");
		}
		czyZakonczyc = 1;
		if (x == 0) {
			czyZakonczyc = 0;
		}
		else {
			if (G1->getPunkty() < 100 && B1->getPunkty() < 100) {
				while (scanf_s("%d", &czyZakonczyc) != 1 || getchar() != '\n' || (czyZakonczyc != 1 && czyZakonczyc != 0)) {
					printf("\nPodano bledne dane, popraw: ");
					cmdClear();
					printf("\n- 1 - TAK");
					printf("\n- 0 - NIE");
					printf("\nCzy chcesz kontynuowac?:\n");
					czysc();
				}
			}
			else {
				czyZakonczyc = 0;
			}
		}

	} while (czyZakonczyc != 0);
	delete temp;
	delete G1;
	delete B1;
}

void multiplayer() {
	printf("\nNazwa pierwszego gracza:\n");
	char N1[dlugoscNicku];
	while (scanf_s("%s", &N1, dlugoscNicku) != 1 || getchar() != '\n') {
		printf("\nPodano bledne dane, popraw: ");
		czysc();
	}

	printf("\nNazwa drugiego gracza:\n");
	char N2[dlugoscNicku];
	while (scanf_s("%s", &N2, dlugoscNicku) != 1 || getchar() != '\n') {
		printf("\nPodano bledne dane, popraw: ");
		czysc();
	}
	kamienieGracza* temp = new kamienieGracza();
	czlowiek* G1 = new czlowiek(N1, 0, &temp);

	czlowiek* G2 = new czlowiek(N2, 1, &temp);

	int wygraneGracza1 = 0, wygraneGracza2 = 0;
	int x = -1;
	int czyZakonczyc = 1;
	int ktoPierwszy = 1;
	do {
		x = runda(G1, G2, N1, N2, ktoPierwszy);
		printf("\nRunda zakonczona. ");
		system("pause");
		cmdClear();
		if (x == 1) {
			wygraneGracza1++;
			ktoPierwszy = 1;
		}
		else if (x == 2) {
			wygraneGracza2++;
			ktoPierwszy = 2;
		}
		if (G1->getPunkty() < 100 && G2->getPunkty() < 100) {
			printf("\n############################\n");
			printf("Postep gry:\n\n");
			printf("%s:\n", G1->getNick());
			printf("Punkty: %d\n", G1->getPunkty());
			printf("Wygrane rundy: %d\n\n", wygraneGracza1);
			printf("%s:\n", G2->getNick());
			printf("Punkty: %d\n", G2->getPunkty());
			printf("Wygrane rundy: %d\n\n", wygraneGracza2);
			printf("\n############################\n");
			system("pause");
		}
		else if (G1->getPunkty() >= 100) {
			printf("\n############################\n");
			printf("############################\n");
			printf("\nGRE WYGRAL: %s\n", G1->getNick());
			printf("\n############################");
			printf("\n############################\n");
			zapiszDoPliku("wynikiDomino.txt", 1, 0, G1->getNick(), wygraneGracza1, G1->getPunkty(), G2->getNick(), wygraneGracza2, G2->getPunkty());
			system("pause");
		}
		else {
			printf("\n############################\n");
			printf("############################\n");
			printf("\nGRE WYGRAL: %s\n", G2->getNick());
			printf("\n############################");
			printf("\n############################\n");
			zapiszDoPliku("wynikiDomino.txt", 2, 0, G1->getNick(), wygraneGracza1, G1->getPunkty(), G2->getNick(), wygraneGracza2, G2->getPunkty());
			system("pause");
		}
		cmdClear();
		if ((G1->getPunkty() < 100 && G2->getPunkty() < 100) && x != 0) {
			printf("\n- 1 - TAK");
			printf("\n- 0 - NIE");
			printf("\nCzy chcesz kontynuowac?:\n");
		}

		czyZakonczyc = 1;
		if (x == 0) {
			czyZakonczyc = 0;
		}
		else {
			if (G1->getPunkty() < 100 && G2->getPunkty() < 100) {
				while (scanf_s("%d", &czyZakonczyc) != 1 || getchar() != '\n' || (czyZakonczyc != 1 && czyZakonczyc != 0)) {
					printf("\nPodano bledne dane, popraw: ");
					cmdClear();
					printf("\n- 1 - TAK");
					printf("\n- 0 - NIE");
					printf("\nCzy chcesz kontynuowac?:\n");
					czysc();
				}
			}
			else {
				czyZakonczyc = 0;
			}
		}

	} while (czyZakonczyc != 0);
	delete temp;
}