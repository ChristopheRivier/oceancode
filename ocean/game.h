
#ifndef GAME_H
#define GAME_H
#include <vector>

#include "carte.h"
#include "infoboucle.h"
#include "zoneOpp.h"
#include "action.h"

//bool debug = true; //#pragma  suppress in the concat file

class Game {
	Carte c;
	std::vector<InfoBoucle> tour;
	std::vector<std::string> deplacementOpp;
	ZoneOpp zone;
	std::vector<Point> lstPossible;
	Point init;
	bool debug;
	Actions actPrec; //action précédente
public:

	Game() :init(-1,-1),debug(false){}

	Game(bool a) :init(-1, -1), debug(a) {}

	void addCarte(Carte& car) { c = car; }
	void addBoucle(InfoBoucle& b) {
		//test si action a porté
		//TODO faire un TU
		if (actPrec.getTir().x != -1 ){
			std::vector<Point> tmp ;

			for (std::vector<Point>::iterator it = lstPossible.begin();
				it != lstPossible.end();
				++it) {
				if ((*it) == actPrec.getTir() &&
					b.getOppLife() + 2 == (*tour.rbegin()).getOppLife()
					) {
					tmp.push_back(*it);
				}
				else if (b.getOppLife() + 1 == (*tour.rbegin()).getOppLife() &&
					(*it).x <= actPrec.getTir().x + 1 && (*it).x >= actPrec.getTir().x - 1 &&
					(*it).y <= actPrec.getTir().y + 1 && (*it).y >= actPrec.getTir().y - 1) {
					tmp.push_back(*it);
				}
				else if (b.getOppLife() == (*tour.rbegin()).getOppLife() &&
					(*it) != actPrec.getTir() ) {//pas toucher
					tmp.push_back(*it);
				}
			}
			lstPossible = tmp;
		}
		tour.push_back(b);
		if (init.x != -1)
			c.position(init);
		else
			c.position(b.getPos());
		if (!b.getMove().empty()) {
			zone.move(b.getMove());
			calculDesPossibleInc(b.getMove());
			deplacementOpp.push_back(b.getMove());
		}
		else if (b.getSurface() != -1) {
			deplacementOpp.clear();
			zone.init();
			//clean des possibles
			cleanPossible(b.getSurface());
		}
		if (b.getTir().x != -1) {
			cleanPossibleNear(b.getTir());
		}
	}
	void cleanPossibleNear(Point a) {
		std::vector<Point> tmp;
		for (std::vector<Point>::iterator it = lstPossible.begin();
			it != lstPossible.end();
			++it) {
			int x = (*it).x - a.x;
			int y = (*it).y - a.y;
			if (abs(x) + abs(y) <= 4) {
				tmp.push_back(*it);
			}
		}
		lstPossible.clear();
		lstPossible = tmp;
	}
	void cleanPossible(int z) {
		//todo
		int zonex = (z-1) % 3;
		int zoney = (z-1) / 3;
		std::vector<Point> tmp;
		for (std::vector<Point>::iterator it = lstPossible.begin();
			it != lstPossible.end();
			++it) {
			if ((*it).x >= 0 +zonex*5 &&
				(*it).x <= 4 + zonex * 5 &&
				(*it).y >= 0 + zoney * 5 &&
				(*it).y <= 4 + zoney * 5 
				) {
				tmp.push_back(*it);
			}
		}
		lstPossible.clear();
		lstPossible = tmp;
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
		if (lstPossible.size() < 15 && lstPossible.size()>0) {
			Point as = a;
			std::string dep = getPrivilegeDirection(a, lstPossible[0]);
			if (!dep.empty() &&
				as.go(dep[0]) &&
				c.deplacementPossible(as)) {
				return dep;
			}
		}

		double nord = -100;
		if (a.N())
			nord = c.calcDeplacement(0, a.getN(), "N");
		double sud = -100;
		if (a.S())
			sud = c.calcDeplacement(0, a.getS(), "S");
		double est = -100;
		if (a.E())
			est = c.calcDeplacement(0, a.getE(), "E");
		double ouest = -100;
		if (a.W())
			ouest = c.calcDeplacement(0, a.getW(), "W");

		if (nord < -60 &&
			sud < -60 &&
			est < -60 &&
			ouest < -60)
			return "";

		if (nord >= sud &&
			nord >= est &&
			nord >= ouest)
			return "N";
		if (sud >= nord &&
			sud >= est &&
			sud >= ouest)
			return "S";
		if (est >= nord &&
			est >= sud &&
			est >= ouest)
			return "E";
		if (ouest >= est &&
			ouest >= sud &&
			ouest >= nord)
			return "W";
	}
	std::string getPrivilegeDirection(Point a,Point b) {
		int x = a.x - b.x;
		int y = a.y - b.y;
		if (abs(y) <= 1 && x <= 1)
			return "";
		if (abs(x) > abs(y)) {
			if (x > 0)
				return "W";
			else
				return "E";
		}
		else {
			if (y > 0)
				return "N";
			else
				return "S";
		}
	}
	bool positionPossibleWithReversePath(Point p, std::string from, std::vector<std::string> it) {
		if (it.size() == 0)
			return true;
		std::string to = *(it.rbegin());
		if (from.compare("N") == 0 && to.compare("S") == 0 ||
			from.compare("S") == 0 && to.compare("N") == 0 ||
			from.compare("W") == 0 && to.compare("E") == 0 ||
			from.compare("E") == 0 && to.compare("W") == 0
			)
			return false;
		if (from.compare("N") == 0 && p.goS() && !c.isIsland(p)) {
			it.pop_back();
			return positionPossibleWithReversePath(p, to, it);
		}
		if (from.compare("S") == 0 && p.goN() && !c.isIsland(p)) {
			it.pop_back();
			return positionPossibleWithReversePath(p, to, it);
		}
		if (from.compare("E") == 0 && p.goW() && !c.isIsland(p)) {
			it.pop_back();
			return positionPossibleWithReversePath(p, to, it);
		}
		if (from.compare("W") == 0 && p.goE() && !c.isIsland(p)) {
			it.pop_back();
			return positionPossibleWithReversePath(p, to, it);
		}
		if (from.compare("?") == 0) {
			Point a = p;
			it.pop_back();
			bool ret = false;
			if (to.compare("S")!=0 && a.goS() && !c.isIsland(a)) {
				ret = ret || positionPossibleWithReversePath(a, to, it);
			}
			a = p;
			if (to.compare("N")!=0 && a.goN() && !c.isIsland(a)) {
				ret = ret || positionPossibleWithReversePath(a, to, it);
			}
			a = p;
			if (to.compare("W")!=0 && a.goW() && !c.isIsland(a)) {
				ret = ret || positionPossibleWithReversePath(a, to, it);
			}
			a = p;
			if (to.compare("E")!=0 && a.goE() && !c.isIsland(a)) {
				ret = ret || positionPossibleWithReversePath(a, to, it);
			}
			return ret;
		}
		return false;
	}

	Point isNear(Point pos) {
		Point ret(-1, -1);
		for (std::vector<Point>::iterator it = lstPossible.begin(); it != lstPossible.end() && ret.x == -1; ++it) {
			int x = (*it).x - pos.x;
			int y = (*it).y - pos.y;
			if (abs(x)+abs(y) <=4) {
				if (debug) {
					std::cerr << " possible" << (*it).toString() << std::endl;
				}
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
			if (w[0] == '?') {
				Point a = *it;
				bool ret = false;
				if ( a.goS() && !c.isIsland(a) && positionPossibleWithReversePath(a, "S", deplacementOpp)) {
					if(std::find(tmp.begin(),tmp.end(),a)==tmp.end())
						tmp.push_back(a);
				}
				a = *it;
				if (a.goN() && !c.isIsland(a) && positionPossibleWithReversePath(a, "N", deplacementOpp)) {
					if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
						tmp.push_back(a);
				}
				a = *it;
				if (a.goW() && !c.isIsland(a) && positionPossibleWithReversePath(a, "W", deplacementOpp)) {
					if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
						tmp.push_back(a);
				}
				a = *it;	
				if (a.goE() && !c.isIsland(a) && positionPossibleWithReversePath(a, "E", deplacementOpp)) {
					if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
						tmp.push_back(a);
				}
			}else if ((*it).go(w[0]) && !c.isIsland(*it) && positionPossibleWithReversePath(*it,w,deplacementOpp) ) {
				if (std::find(tmp.begin(), tmp.end(), *it) == tmp.end())
					tmp.push_back(*it);
			}
		}
		lstPossible.clear();
		lstPossible = tmp;
	}

	void calculDesPossible() {
		lstPossible.clear();
		std::vector<std::string> ldp = deplacementOpp;
		std::string dp = "";
		if (deplacementOpp.size() > 0) {
			dp = *(deplacementOpp.rbegin());
			ldp.pop_back();
		}
		for (int i = 0; i < 15 - (zone.getLargeur() - 1); ++i) {
			for (int j = 0; j < 15 - (zone.getHauteur() - 1); ++j) {
				Point p = zone.getPosition();
				p.x += i;
				p.y += j;
				if ((!c.isIsland(p)) && positionPossibleWithReversePath(p,dp,ldp)) {
					lstPossible.push_back(p);
				}
			}
		}
	}
	std::vector<Point> getLstPossible() {
		return lstPossible;
	}
	/** a utiliser pour les tests uniquement*/
	void setLstPossible(std::vector<Point> lst) {
		lstPossible = lst;
	}

	std::string getPower() {
		std::string s = "TORPEDO";
		InfoBoucle i = *tour.rbegin();
		if (i.getTorpe() != 0) {
			s = "TORPEDO";
		}
		else if (i.getTorpe() == 0 && i.getSilence()!=0 ) {
			s = "SILENCE";
		}
		else {
			s = "SONAR";
		}
		return s;
	}

	std::string getMove() {
		actPrec.init();
		std::string dep = calculDeplacement();
		std::string ret = "MOVE ";
		bool power = false;
		if (dep.empty()) {
			ret = "SURFACE";
			init = (*tour.rbegin()).getPos();
			c.clear();
		}
		else {
			actPrec.setDirection(dep);
			if ((*tour.rbegin()).getSilence() == 0) {
				ret = "SILENCE " + dep + " 1";
			}
			else {
				power = true;
				ret += dep;
			}
		}
		if ((*tour.rbegin()).getTorpe() == 0 && getLstPossible().size()<10) {
			if(getLstPossible().size()==0)
				calculDesPossible();
			Point n = isNear((*tour.rbegin()).getPos());
			if (n.x!=-1) {
				actPrec.setTir(n);
				ret += "|TORPEDO " + n.toString();
			}else if(power)
				ret += " " + getPower();
		}
		else if(power)
			ret += " " + getPower();
		return ret;
	}
};

#endif
