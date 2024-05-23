#ifndef plansza_h
#define plansza_h

#include "kamien.h"

class plansza {
private:
	kamien* kamienNaPlanszy;	//adres kamienia na planszy
public:
	plansza* nast;

	kamien* getKamienNaPlanszy();	//zwraca adres kamienia na planszy

	plansza();
	plansza(kamien* k);
	~plansza();
};

void dodajDoPlanszy(plansza** p, kamien* k, int LewoPrawo, int obrot);	
//dodaje kamien o adresie "k" do planszy zaleznie z okreslonej strony planszy, o okreslonym obrocie kamienia

void wypiszPlansze(plansza** head);	//wypisuje plansze o glowie "head"

#endif