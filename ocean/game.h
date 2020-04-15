
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
	std::vector<Point> lstMine;
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
					b.getOppLife() + 2 <= (*tour.rbegin()).getOppLife()
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
		// iterate on action list
		for (std::vector<Action>::iterator it = b.getLstAction().begin(); it != b.getLstAction().end(); ++it) {
			if ((*it).getType() == Action::Move|| (*it).getType() == Action::Silence) {
				zone.move((*it).getDep());

				if (lstPossible.size() == 0)
					calculDesPossible();
				else
					calculDesPossibleInc((*it).getDep());
				deplacementOpp.push_back((*it).getDep());
			}
			else if ((*it).getType() == Action::Surface) {
				deplacementOpp.clear();
				zone.init();
				//clean des possibles
				cleanPossible((*it).getZone());
			}
			else if ((*it).getType() == Action::Torpedo) {
				cleanPossibleNear((*it).getPos());
			}
		}
	}
	void printLstPossible(std::string s) {
		for (std::vector<Point>::iterator i = lstPossible.begin();
			i != lstPossible.end();
			++i) {
			//				std::cerr << (*i).toString() << endl;
			std::cerr << (*i).toString() << std::endl;

			if ((*i).y > 15)
				std::cerr << " before "<< s<<" ----------------------------------------------------- " << std::endl;

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
		if (tmp.size() == 0) {
			int maxx = a.x + 4>14?14: a.x + 4;
			int maxy = a.y + 4 > 14 ? 14 : a.y + 4;
			for (int x = abs(a.x-4); x <= maxx; ++x) {
				for (int y = abs(a.y-4); y <= maxy; ++y)
					if( abs(x-a.x)+abs(y-a.y) <=4 && c.deplacementPossible(Point(x, y)))
						tmp.push_back(Point(x, y));
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
		if (tmp.size() == 0) {
			for (int x = 0 + zonex * 5; x <= 4 + zonex * 5; ++x) {
				for (int y = 0 + zoney * 5; y <= 4 + zoney * 5; ++y)
					if (c.deplacementPossible(Point(x, y)))
						tmp.push_back(Point(x, y));
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
		int t = -100;
		if (nord <= t &&
			sud <= t &&
			est <= t &&
			ouest <= t)
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
		return "";
	}
	std::string getPrivilegeDirection(Point a,Point b) {
		int x = a.x - b.x;
		int y = a.y - b.y;
		if (abs(y) < 2 && abs(x) < 2)
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
	bool positionPossibleWithReversePath(Point p, std::string from, std::vector<std::string> it, std::vector<Point> pass, int incSilence) {
		if (it.size() == 0 && incSilence==0 && from.empty() )
			return true;
		std::string to;
		if(it.size() != 0 )
			to = *(it.rbegin());
		if (from.compare("N") == 0 && to.compare("S") == 0 ||
			from.compare("S") == 0 && to.compare("N") == 0 ||
			from.compare("W") == 0 && to.compare("E") == 0 ||
			from.compare("E") == 0 && to.compare("W") == 0
			)
			return false;
		pass.push_back(p);
		if (incSilence == 0)
		{
			if (from.compare("N") == 0 && p.goS() && !c.isIsland(p) && std::find(pass.begin(), pass.end(), p) == pass.end()) {
				if (it.size() != 0)
					it.pop_back();
				return positionPossibleWithReversePath(p, to, it, pass, incSilence);
			}
			if (from.compare("S") == 0 && p.goN() && !c.isIsland(p) && std::find(pass.begin(), pass.end(), p) == pass.end()) {
				if (it.size() != 0)
					it.pop_back();
				return positionPossibleWithReversePath(p, to, it, pass, incSilence);
			}
			if (from.compare("E") == 0 && p.goW() && !c.isIsland(p) && std::find(pass.begin(), pass.end(), p) == pass.end()) {
				if (it.size() != 0)
					it.pop_back();
				return positionPossibleWithReversePath(p, to, it, pass, incSilence);
			}
			if (from.compare("W") == 0 && p.goE() && !c.isIsland(p) && std::find(pass.begin(), pass.end(), p) == pass.end()) {
				if (it.size() != 0)
					it.pop_back();
				return positionPossibleWithReversePath(p, to, it, pass, incSilence);
			}
			if (from.compare("?") == 0) {
				Point a = p;
				bool ret = false;
				if (to.compare("S") != 0 && a.goS() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
					ret = ret || positionPossibleWithReversePath(a, "N", it, pass, 1);
					if (a.goS() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
						ret = ret || positionPossibleWithReversePath(a, "N", it, pass, 2);
						if (a.goS() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
							ret = ret || positionPossibleWithReversePath(a, "N", it, pass, 3);
							if (a.goS() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
								ret = ret || positionPossibleWithReversePath(a, "N", it, pass, 4);
							}
						}
					}
				}
				a = p;
				if (to.compare("N") != 0 && a.goN() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
					ret = ret || positionPossibleWithReversePath(a, "S", it, pass, 1);
					if (a.goN() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
						ret = ret || positionPossibleWithReversePath(a, "S", it, pass, 2);
						if (a.goN() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
							ret = ret || positionPossibleWithReversePath(a, "S", it, pass, 3);
							if (a.goN() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
								ret = ret || positionPossibleWithReversePath(a, "S", it, pass, 4);

							}
						}
					}
				}
				a = p;
				if (to.compare("W") != 0 && a.goW() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
					ret = ret || positionPossibleWithReversePath(a, "E", it, pass, 1);				
					if (a.goW() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
						ret = ret || positionPossibleWithReversePath(a, "E", it, pass, 2);
						if (a.goW() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
							ret = ret || positionPossibleWithReversePath(a, "E", it, pass, 3);
							if (a.goW() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
								ret = ret || positionPossibleWithReversePath(a, "E", it, pass, 4);
							}
						}
					}
				}
				a = p;
				if (to.compare("E") != 0 && a.goE() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
					ret = ret || positionPossibleWithReversePath(a, "W", it, pass, 1);
					if (a.goE() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
						ret = ret || positionPossibleWithReversePath(a, "W", it, pass, 2);
						if (a.goE() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
							ret = ret || positionPossibleWithReversePath(a, "W", it, pass, 3);
							if (a.goE() && !c.isIsland(a) && std::find(pass.begin(), pass.end(), a) == pass.end()) {
								ret = ret || positionPossibleWithReversePath(a, "W", it, pass, 4);
							}
						}
					}
				}
				if (it.size() != 0)
					it.pop_back();
				ret = ret | positionPossibleWithReversePath(p, to, it, pass,0);
				return ret;
			}
		}
		else
		{
			// on decremente avec les mêmes arguments
			--incSilence;
			Point tt = p.getInv(from[0]);

			if (incSilence == 0) {
				if (!c.isIsland(tt) && std::find(pass.begin(), pass.end(), tt) == pass.end()) {
					if (it.size() != 0)
						it.pop_back();
					return positionPossibleWithReversePath(tt, to, it, pass, incSilence);
				}
				else
					return false;
			}
			else {
				if (!c.isIsland(tt) && std::find(pass.begin(), pass.end(), tt) == pass.end())
					return positionPossibleWithReversePath(tt, from, it, pass, incSilence);
				else
					return false;
			}
		}
		
		return false;
	}

	Point isNear(Point pos) {
		Point ret(-1, -1);
		for (std::vector<Point>::iterator it = lstPossible.begin(); it != lstPossible.end() && ret.x == -1; ++it) {
			int x = (*it).x - pos.x;
			int y = (*it).y - pos.y;
			if (abs(x)+abs(y) <=4 && abs(x) + abs(y) >= 1 ) {
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
			std::vector<Point> lstPass;
			if (w[0] == '?') {
				Point a = *it;
				//cas force 0
				if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
					tmp.push_back(a);

				bool ret = false;
				if ( a.goS() && !c.isIsland(a) && positionPossibleWithReversePath(a, "S", deplacementOpp, lstPass,1)) {
					if(std::find(tmp.begin(),tmp.end(),a)==tmp.end())
						tmp.push_back(a);
					if (a.goS() && !c.isIsland(a) && positionPossibleWithReversePath(a, "S", deplacementOpp, lstPass, 2)) {
						if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
							tmp.push_back(a);
						if (a.goS() && !c.isIsland(a) && positionPossibleWithReversePath(a, "S", deplacementOpp, lstPass, 3)) {
							if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
								tmp.push_back(a);
						}
						if (a.goS() && !c.isIsland(a) && positionPossibleWithReversePath(a, "S", deplacementOpp, lstPass, 4)) {
							if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
								tmp.push_back(a);
						}
					}
				}
				a = *it;
				if (a.goN() && !c.isIsland(a) && positionPossibleWithReversePath(a, "N", deplacementOpp, lstPass,1)) {
					if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
						tmp.push_back(a);
					if (a.goN() && !c.isIsland(a) && positionPossibleWithReversePath(a, "N", deplacementOpp, lstPass, 2)) {
						if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
							tmp.push_back(a);
						if (a.goN() && !c.isIsland(a) && positionPossibleWithReversePath(a, "N", deplacementOpp, lstPass, 3)) {
							if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
								tmp.push_back(a);
							if (a.goN() && !c.isIsland(a) && positionPossibleWithReversePath(a, "N", deplacementOpp, lstPass, 4)) {
								if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
									tmp.push_back(a);
							}
						}
					}
				}
				a = *it;
				if (a.goW() && !c.isIsland(a) && positionPossibleWithReversePath(a, "W", deplacementOpp, lstPass,1)) {
					if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
						tmp.push_back(a);
					if (a.goW() && !c.isIsland(a) && positionPossibleWithReversePath(a, "W", deplacementOpp, lstPass, 2)) {
						if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
							tmp.push_back(a);
						if (a.goW() && !c.isIsland(a) && positionPossibleWithReversePath(a, "W", deplacementOpp, lstPass, 3)) {
							if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
								tmp.push_back(a);
							if (a.goW() && !c.isIsland(a) && positionPossibleWithReversePath(a, "W", deplacementOpp, lstPass, 4)) {
								if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
									tmp.push_back(a);
							}
						}
					}
				}
				a = *it;	
				if (a.goE() && !c.isIsland(a) && positionPossibleWithReversePath(a, "E", deplacementOpp, lstPass,1)) {
					if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
						tmp.push_back(a);
					if (a.goE() && !c.isIsland(a) && positionPossibleWithReversePath(a, "E", deplacementOpp, lstPass, 2)) {
						if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
							tmp.push_back(a);
						if (a.goE() && !c.isIsland(a) && positionPossibleWithReversePath(a, "E", deplacementOpp, lstPass, 3)) {
							if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
								tmp.push_back(a);
							if (a.goE() && !c.isIsland(a) && positionPossibleWithReversePath(a, "E", deplacementOpp, lstPass, 4)) {
								if (std::find(tmp.begin(), tmp.end(), a) == tmp.end())
									tmp.push_back(a);
							}
						}
					}
				}
			}else if ((*it).go(w[0]) && !c.isIsland(*it) && positionPossibleWithReversePath(*it,w,deplacementOpp, lstPass,0) ) {
				if (std::find(tmp.begin(), tmp.end(), *it) == tmp.end()) {
					tmp.push_back(*it);
				}
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
				std::vector<Point> lstPass;
				if ((!c.isIsland(p)) && positionPossibleWithReversePath(p,dp,ldp,lstPass,0)) {
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
		else if (i.getMine() != 0 && ( (c.getTailleChemin()>21 && c.getTailleChemin() <50) || i.getSilence()==0 ))
			s = "MINE";
		else if (i.getTorpe() == 0 && i.getSilence()!=0 ) {
			s = "SILENCE";
		}
		else if (i.getSonar() != 0) {
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
				Point e = (*tour.rbegin()).getPos().get(dep[0]);
				std::string force = " 1";
				if (e.is(dep[0]) && c.deplacementPossible(e.get(dep[0]))) {
					force = " 2";
					c.position(e);
				}
				ret = "SILENCE " + dep + force;
			}
			else {
				power = true;
				ret += dep;
			}
		}
		if ((*tour.rbegin()).getTorpe() == 0 && lstPossible.size()<10) {
			Point n = isNear((*tour.rbegin()).getPos());
			if (n.x!=-1) {
				actPrec.setTir(n);
				ret = "TORPEDO " + n.toString()+"|"+ret;
			}
			if(power)
				ret += " " + getPower();
		}
		else if(power)
			ret += " " + getPower();
		if ((*tour.rbegin()).getTorpe() < 2  && (*tour.rbegin()).getMine() == 0) {
			lstMine.push_back((*tour.rbegin()).getPos().get(dep[0]));
			if (dep.empty()) {
				Point e = (*tour.rbegin()).getPos().get(dep[0]);
				if (c.deplacementPossible(e.getN()))
					dep = "N";
				else if (c.deplacementPossible(e.getS()))
					dep = "S";
				else if (c.deplacementPossible(e.getE()))
					dep = "E";
				else if (c.deplacementPossible(e.getW()))
					dep = "W";
			}
			ret = "MINE " + dep+"|"+ret;
		}
		//trigger the mine
		if (lstPossible.size() < 10) {
			bool end = true;
			for (std::vector<Point>::iterator it = lstPossible.begin();
				it != lstPossible.end() && end; ++it) {
				std::vector<Point> tmp;
				for (std::vector<Point>::iterator itmine = lstMine.begin();
					itmine != lstMine.end() && end;
					++itmine
					) {
		//			std::cerr << " mine " << (*itmine).toString() << std::endl;
					int x = (*it).x - (*itmine).x;
					int y = (*it).y - (*itmine).y;
					if (abs(x) + abs(y) <= 1 && abs(x) + abs(y) >= 0) {
						ret += "|TRIGGER " + (*itmine).toString();
						end = false;
					}
					else
						tmp.push_back((*itmine));
				}
				lstMine = tmp;
			}
		}
		return ret;
	}
	int getsize() { return lstPossible.size(); }
};

#endif
