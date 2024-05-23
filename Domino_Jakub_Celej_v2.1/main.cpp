#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "misc.h"
#include "gra.h"


int main() {
	printf("Autor: Jakub Celej\n\n");
	srand((unsigned int)time(NULL));

	do {
		stronaTytulowa();
		int wybor;
		printf("\n\n\nTwoj wybor: ");
		while (scanf_s("%d", &wybor) != 1 || getchar() != '\n' || (wybor != 1 && wybor != 2 && wybor != 3 && wybor != 4)) {
			cmdClear();
			stronaTytulowa();
			printf("\n\nPodano bledne dane, popraw: ");
			printf("\nTwoj wybor: ");
			czysc();
		}

		switch (wybor) {
		case 1:
			singleplayer();
			break;
		case 2:
			multiplayer();
			break;
		case 3:
			cmdClear();
			std::cout << "======================" << endl << "ROZEGRANE GRY" << endl << "======================" << endl << endl;
			FILE * tempF;
			if ((tempF = fopen("wynikiDomino.txt", "r")) == NULL) {
				printf("\nNie otworzono pliku %s", "wynikiDomino.txt");
				exit(1);
			}

			if (tempF != 0) {
				int i = 0, strona = 1, czyWyjscZListy = 1;
				while (!feof(tempF)) {
					char nazwa1[dlugoscNicku], nazwa2[dlugoscNicku];
					int punkt1 = 0, punkt2 = 0, wygra1 = 0, wygra2 = 0, kto = 0, bot = 0;
					if (fscanf(tempF, "%d %d %s %d %d %s %d %d", &kto, &bot, nazwa1, &wygra1, &punkt1, nazwa2, &wygra2, &punkt2) == 8) {
						if (bot == 0) {
							printf("GraczVsGracz:    %s - Wygrane: %d - Punkty: %d |  %s - Wygrane: %d - Punkty: %d | ", nazwa1, wygra1, punkt1, nazwa2, wygra2, punkt2);
							if (kto == 1) {
								printf("Wygral: %s\n", nazwa1);
							}
							else {
								printf("Wygral: %s\n", nazwa2);
							}
						}
						else {
							printf("GraczVsKomputer: %s - Wygrane: %d - Punkty: %d |  %s - Wygrane: %d - Punkty: %d | ", nazwa1, wygra1, punkt1, nazwa2, wygra2, punkt2);
							if (kto == 1) {
								printf("Wygral: %s\n", nazwa1);
							}
							else {
								printf("Wygral: %s\n", nazwa2);
							}
						}
					}
					i++;
					if (i % 10 == 0) {
						std::cout << endl << "Strona " << strona << endl;
						system("pause");
						cmdClear();
						std::cout << "======================" << endl << "ROZEGRANE GRY" << endl << "======================" << endl << endl;
						strona++;
					}
					if (i % 50 == 0) {
						std::cout << endl << endl << "- 1 - TAK" << endl << "- 0 - NIE" << endl << "Czy chcesz kontynuowac wypisywanie listy?: ";
						while (scanf_s("%d", &czyWyjscZListy) != 1 || getchar() != '\n' || (czyWyjscZListy != 1 && czyWyjscZListy != 0)) {
							cmdClear();
							std::cout << endl << endl << "- 1 - TAK" << endl << "- 0 - NIE" << endl << "Czy chcesz kontynuowac wypisywanie listy?: ";
							std::cout << endl << endl << "Podano bledne dane, popraw: ";
							czysc();
						}
						if (czyWyjscZListy == 0) {
							break;
						}
						else {
							cmdClear();
							std::cout << "======================" << endl << "ROZEGRANE GRY" << endl << "======================" << endl << endl;
						}
					}
				}
				if (czyWyjscZListy != 0) {
					std::cout << endl << endl << "--- Koniec listy ---" << endl;
					system("pause");
				}
			}

			if (tempF != NULL) {
				fclose(tempF);
			}
			break;
		case 4:
			std::cout << endl << endl << "Koniec programu." << endl;
			return 0;
		default:
			std::cout << endl << endl << "Blad. Koniec programu." << endl;
			return 0;
		}
	} while (1);
	std::cout << endl << endl << "Koniec programu." << endl;
	return 0;
}