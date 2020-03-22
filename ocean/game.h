
#ifndef GAME_H
#define GAME_H
#include <vector>
#include "carte.h"
#include "infoboucle.h"
class Game {
	Carte c;
	std::vector<InfoBoucle> tour;
public:
	Game() {}
	void addCarte(Carte& car) { c = car; }
	void addBoucle(InfoBoucle& b) { tour.push_back( b ); }
	void modifCarte(int i, std::string l) { c.addLine(i, l); }

	std::string calculDeplacement() {
		InfoBoucle& bou = *(tour.rbegin());
		Point a = bou.getPos();
		if (c.deplacementPossible(a.getN())) {
			return "N";
		}
		else if (c.deplacementPossible(a.getE())) {
			return "E";
		}
		else if (c.deplacementPossible(a.getS())) {
			return "S";
		}
		else if (c.deplacementPossible(a.getW())) {
			return "W";
		}
		return "";
	}

};

#endif
