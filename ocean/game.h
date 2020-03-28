
#ifndef GAME_H
#define GAME_H
#include <vector>
#include "carte.h"
#include "infoboucle.h"
#include "zoneOpp.h"

class Game {
	Carte c;
	std::vector<InfoBoucle> tour;
	std::vector<std::string> deplacementOpp;
	ZoneOpp zone;
	std::vector<Point> lstPossible;
	Point init;
public:

	Game() :init(-1,-1){}
	void addCarte(Carte& car) { c = car; }
	void addBoucle(InfoBoucle& b) {
		tour.push_back(b);
		if (init.x != -1)
			c.position(init);
		else
			c.position(b.getPos());
		if (!b.getMove().empty()) {
			deplacementOpp.push_back(b.getMove());
			zone.move(b.getMove());
			calculDesPossibleInc(b.getMove());
		}
		else if (b.getSurface() != -1) {
			deplacementOpp.clear();
			zone.init();
			//clean des possibles
			cleanPossible();
		}
	}
	void cleanPossible() {
		//todo
	}

	int getHauteur() { return zone.getHauteur(); }
	int getLargeur() { return zone.getLargeur(); }
	Point getPositionOpp() { return zone.getPosition(); }
	void modifCarte(int i, std::string l) { c.addLine(i, l); }

	std::string getLastDeplacement() {
		if (deplacementOpp.size() == 0)
			return "";
		return *(deplacementOpp.rbegin());
	}

	std::string calculDeplacement() {
		InfoBoucle& bou = *(tour.rbegin());
		Point a;
		if (init.x == -1) {
			a = bou.getPos();
		}
		else {
			a = init;
			init = Point(-1, -1);
		}

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

	bool positionPossibleWithReversePath(Point p) {
		bool ret = true;
		for (std::vector<std::string>::reverse_iterator it = deplacementOpp.rbegin();
			it != deplacementOpp.rend();
			++it) {
			if (((*it).compare("N") == 0 && p.goS() && !c.isIsland(p)) ||
				((*it).compare("S") == 0 && p.goN() && !c.isIsland(p)) ||
				((*it).compare("E") == 0 && p.goW() && !c.isIsland(p)) ||
				((*it).compare("W") == 0 && p.goE() && !c.isIsland(p))
				) {
				continue;
			}
			else {
				ret = false;
				break;
			}
		}
		return ret;
	}
	Point isNear() {
		Point ret(-1, -1);
		InfoBoucle t = *tour.rbegin();
		Point pos = t.getPos();
		for (std::vector<Point>::iterator it = lstPossible.begin(); it != lstPossible.end() && ret.x == -1; ++it) {
			int x = (*it).x - pos.x;
			int y = (*it).y - pos.y;
			if (x <=4 && x>=-4 && y <= 4 && y>=-4) {
				ret = *it;
			}
		}
		return ret;
	}

	void calculDesPossibleInc(std::string w) {
		std::vector<Point> tmp;
		for (std::vector<Point>::iterator it = lstPossible.begin();
			it != lstPossible.end();
			++it) {
			if ((*it).go(w[0]) && positionPossibleWithReversePath(*it) ) {
				tmp.push_back(*it);
			}
		}
		lstPossible.clear();
		lstPossible = tmp;
	}

	void calculDesPossible() {
		lstPossible.clear();
		for (int i = 0; i < 15 - (zone.getLargeur() - 1); ++i) {
			for (int j = 0; j < 15 - (zone.getHauteur() - 1); ++j) {
				Point p = zone.getPosition();
				p.x += i;
				p.y += j;
				if ((!c.isIsland(p)) && positionPossibleWithReversePath(p)) {
					lstPossible.push_back(p);
				}
			}
		}
	}
	std::vector<Point> getLstPossible() {
		return lstPossible;
	}

	std::string getMove() {
		std::string dep = calculDeplacement();
		std::string ret = "MOVE ";
		if (dep.empty()) {
			ret = "SURFACE";
			init = (*tour.rbegin()).getPos();
			c.clear();
		}
		else
			ret += dep ;
		if ((*tour.rbegin()).getTorpe() == 0) {
			if(getLstPossible().size()==0)
				calculDesPossible();
			Point n = isNear();
			if (n.x!=-1) {
				ret += "|TORPEDO " + n.toString();
			}else
				ret += " TORPEDO";
		}
		else
			ret += " TORPEDO";
		return ret;
	}
};

#endif
