#ifndef kamienieGracza_h
#define kamienieGracza_h

#include "kamien.h"
#include "plansza.h"

class kamienieGracza {
private:
	int nrKamienia;	//nr kamienia w puli kamieni nalezacych do gracza 
	//(numerowane od zera do n-1, gdzie n to liczba kamieni nalezacych do gracza, ktore nie zostaly uzyte)
	kamien* kamienReka;	//adres aktualnego kamienia
public:
	kamienieGracza* nast;

	int getNrKamienia();	//zwraca nr kamienia w puli gracza
	kamien* getKamienReka();	//zwraca adres kamienia z puli gracza

	void setNrKamienia(int x);	//ustawia nr kamienia w puli gracza na podana liczbe

	int czyPasujeZLewej(plansza** head);	//sprawdza czy kamien pasuje z lewej w okreslonej rotacji
	int czyPasujeZPrawej(plansza** head);//sprawdza czy kamien pasuje z prawej w okreslonej rotacji

	kamienieGracza();
	kamienieGracza(kamien* dodaj, int nr);
	~kamienieGracza();

};

#endif