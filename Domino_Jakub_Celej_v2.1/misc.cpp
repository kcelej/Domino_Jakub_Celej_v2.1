#include "misc.h"

#include <stdio.h>

void czysc() {
	char c;
	while ((c = getchar()) != '\n' && c != EOF) {

	}
}

void cmdClear() {
	for (int i = 0; i < 100; i++) {
		putchar('\n');
	}
}

void stronaTytulowa() {
	cmdClear();
	std::cout <<"  _____                  _             " << endl;
	std::cout << " |  __ \\                (_)            " << endl;
	std::cout << " | |  | | ___  _ __ ___  _ _ __   ___  " << endl;
	std::cout << " | |  | |/ _ \\| '_ ` _ \\| | '_ \\ / _ \\ " << endl;
	std::cout << " | |__| | (_) | | | | | | | | | | (_) |" << endl;
	std::cout << " |_____/ \\___/|_| |_| |_|_|_| |_|\\___/ " << endl;
	std::cout << "                                       " << endl << endl;
	std::cout << " Autor: Jakub Celej" << endl;
	std::cout << endl << endl << endl;
	std::cout << "1. Rozpocznij gre w trybie Gracz vs. Komputer." << endl;
	std::cout << "2. Rozpocznij gre w trybie Gracz vs. Gracz." << endl;
	std::cout << "3. Zobacz rozegrane gry." << endl;
	std::cout << "4. Wyjdz." << endl;
}

int czyIstniejePlik(const char nazwaPliku[dlugoscNazwPlikow]) {
	FILE* tempF;
	if ((tempF = fopen(nazwaPliku, "r")) == NULL) {
		return 0;
	}
	else {
		return 1;
	}
	if (tempF != NULL) {
		fclose(tempF);
	}
}

void zapiszDoPliku(const char nazwaPliku[dlugoscNazwPlikow], int ktoWygral, int czyZBotem, char gracz1[dlugoscNicku], int wygrane1, int punkty1, char gracz2[dlugoscNicku], int wygrane2, int punkty2) {
	FILE* tempF;
	if (czyIstniejePlik(nazwaPliku) == 0) {
		if ((tempF = fopen(nazwaPliku, "w")) == NULL) {
			perror("Nie udalo sie utworzyc pliku z wynikami: ");
			system("pause");
		}
	}
	else {
		if ((tempF = fopen(nazwaPliku, "a")) == NULL) {
			perror("Nie udalo sie otworzyc pliku z wynikami: ");
			system("pause");
		}
	}

	if (tempF != 0) {
		fprintf(tempF, "%d %d %s %d %d %s %d %d\n", ktoWygral, czyZBotem, gracz1, wygrane1, punkty1, gracz2, wygrane2, punkty2);
	}
	
	if (tempF != NULL) {
		fclose(tempF);
	}
}