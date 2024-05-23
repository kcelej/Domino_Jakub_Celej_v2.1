#ifndef kamien_h
#define kamien_h

#define ileKamieni 28

class kamien {
private:
	int id;	//identyfikator kamienia
	int gora;	//wartosc oczek na "gornym" polu kamienia
	int dol;	//wartosc oczek na "dolnym" polu kamienia
	int obrotLewoPrawo;	//obrot kamienia | 
	//0 = obrot w lewo [Gora|Dol]; 
	//1 = obrot w prawo [Dol|Gora];
	int nrGracza;	//identyfikator gracza, do ktorego nalezy kamien | 
	//-1 - nalezy do nikogo; 
	//-2 - jest na planszy I nie nalezy do nikogo (na poczatek rundy wykladany na plansze jest losowy kamien z puli); 
	//1 - nalezy do gracza 1; 
	//2 - nalezy do gracza 2;
	int czyNaPlanszy;	//czy kamien znajduje sie na planszy
	//0 = nie; 
	//1 = tak;
public:
	kamien* nast;

	int getID();	//zwraca identyfikator kamienia
	int getGora();	//zwraca wartosc oczek na "gornym" polu kamienia
	int getDol();	//zwracawartosc oczek na "dolnym" polu kamienia
	int getObrot();	//zwraca obrot kamiena
	int getNrGracza();	//zwraca identyfikator gracza, do ktorego nalezy kamien
	int getCzyNaPlanszy();	//zwraca 1 lub 0 w zaleznosci, czy kamien jest uzyty na planszy

	void setObrot(int o);	//ustawia obrot kamienia
	void setNrGracza(int nr);	//ustawia identyfikator gracza do ktorego nalezy kamien
	void setCzyNaPlanszy(int czy);	//ustawia informacje czy kamien jest na planszy

	int czyDubel();	//sprawdza, czy kamien ma te same wartosci na obu polach
	void wypisz();	//wypisuje kamien

	kamien();
	kamien(int ID, int G, int D, int obrot);
	~kamien();
};

int czyJestNieuzytyKamien(kamien** k);	//sprawdza, czy w puli jest nieuzyty jeszcze kamien

kamien* losujNowy(kamien** k);	//losuje nowy, nieuzyty oraz nie znajdujacy sie na planszy kamien

void stworzPuleKamieni(kamien** head);	//tworzy pule kamieni

int ileNiewykorzystanychKamieni(kamien** head);	//sprawdza ile jest niewykorzystanych kamieni w puli

void wypiszPule(kamien** head);	//funkcja do debugowania, wypisuje pule kamieni

#endif