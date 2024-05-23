#include "czlowiek.h"
#include "misc.h"

#include <string.h>

czlowiek::czlowiek() {
	strcpy(nick, "Bezimienny");
}

czlowiek::czlowiek(const char nowyNick[dlugoscNicku], int id, kamienieGracza** h) : gracz(id, h) {
	strcpy(nick, nowyNick);
}

char* czlowiek::getNick() {
	return nick;
}