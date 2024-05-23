#ifndef gracz_h
#define gracz_h

#include "kamienieGracza.h"

#define dlugoscNicku 30

class gracz {
private:
	int id;	//identyfikator gracza
	kamienieGracza* kamienieGraczaGlowa;	//glowa listy skladajacej sie z kamieni nalezacych do gracza
	int punkty;	//punkty, ktore w ciagu rozgrywki zebral gracz
	char nick[dlugoscNicku];	//nazwa gracza (w klasie gracz nazwa jest zawsze nazwa domyslna: "NazwaDomyslna")
public:
	gracz* nast;

	kamienieGracza* getKamienieGraczaGlowa();	//zwraca glowe listy przechowujacej kamienie uzytkownika
	void setKamienieGraczaGlowa(kamienieGracza* h);	//ustawia glowe listy przechowujacej kamienie uzytkownika
	virtual char* getNick();	//zwraca nick uzytkownika
	int getPunkty();	//zwraca ilosc punktow nalezacych do uzytkownika
	int getID();	//zwraca identyfikator uzytkownika
	void setPunkty(int x);	//ustawia punkty uzytkownika na okreslona wartosc
	void dodajPunkty(int x);	//dodaje punkty do sumy punktow uzytkownika
	void dodajKamien(kamien* dodaj);	//dodaje kamien do puli uzytkownika
	void ukryjKamien(int nr);	//ukrywa widocznosc kamienia w puli uzytkownika
	void wypiszKamienieGracza(plansza** p);
	int liczbaKamieniGracza();	//liczba kamieni w puli kamieni nalezacych do gracza
	virtual int wykonajRuch(plansza** p, kamien** pula, gracz* przeciwnik);
	//wykonuje ruch w zaleznosci od decyzji uzytkownika
	int czyPosiadaPasujacyKamien(plansza** p);
	//sprawdza, czy gracz ma kamien pasujacy do planszy w puli kamieni nalezacych do niego
	int sumaOczekWRece();	//suma oczek w kamieniach w puli kamieni nalezacych do gracza, ktore nie zostaly jeszcze uzyte

	gracz();
	gracz(int ID, kamienieGracza** head);
	~gracz();
};

void interfejs(plansza** p, gracz* grajacy, gracz* przeciw, kamien** pulaK);

#endif