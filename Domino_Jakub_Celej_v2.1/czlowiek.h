#ifndef czlowiek_h
#define czlowiek_h

#include "gracz.h"

class czlowiek : public gracz {
private:
	char nick[dlugoscNicku];	//nazwa gracza, nazwe podaje uzytkownik
public:
	czlowiek();
	czlowiek(const char nowyNick[dlugoscNicku], int ID, kamienieGracza** head);

	char* getNick();	//zwraca nazwe czlowieka
};

#endif