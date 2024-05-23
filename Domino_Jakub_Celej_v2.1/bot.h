#ifndef bot_h
#define bot_h

#include "gracz.h"

class bot : public gracz {
private:
	char nick[dlugoscNicku];//nazwa bota/klomputera (w klasie bot nazwa jest zawsze nazwa domyslna: "BOT-Domino")
public:
	bot();
	bot(int id, kamienieGracza** h);

	int wykonajRuch(plansza** p, kamien** pula, gracz* przeciwnik);	//wykonuje ruch automatycznie
	char* getNick();	//zwraca nazwe bota
};

#endif