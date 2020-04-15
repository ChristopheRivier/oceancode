#ifndef INFOBOUCLE
#define INFOBOUCLE


#include <string>
#include "point.h"
#include "action.h"
#include <sstream>

class InfoBoucle {
	Point pos;
	int mylife;
	int opplife;
	int torpe;
	int sonar;
	int silence;
	int mine;

	std::string sonarRes;
	std::string order;
	
	std::vector<Action> lstAction;

public:
	int getOppLife() { return opplife; }
	InfoBoucle(int x, int y, int l, int o, int t, int s, int q, int m):pos(x,y),mylife(l),opplife(o),torpe(t), sonar(s), silence(q),
		mine(m){}
	void addSonar(std::string s) {
		sonarRes = s;
	}
	void addOrder(std::string o) {
		order = o;
		//init variable
		lstAction.clear();
		std::vector<std::string> list = split(o, '|');
		for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it) {
			lstAction.push_back(Action((*it)));
		}
	}
	std::vector<Action> &getLstAction() { return lstAction; }
	std::string print() {
		std::string s;
		s = pos.toString() + " " + std::to_string(mylife) + " " + std::to_string(opplife) + " " + std::to_string(torpe) + " " + std::to_string(sonar) + " " + std::to_string(silence) + " " + std::to_string(mine);
		s += "\n";
		s += sonarRes;
		s += "\n";
		s += order;

/*
		std::string s;
		s = "boul = InfoBoucle(";
		s += std::to_string(pos.x) + "," + to_string(pos.y) + ", " + std::to_string(mylife) + ", " + std::to_string(opplife) + ", " + std::to_string(torpe) + ", " + std::to_string(sonar) + ", " + std::to_string(silence) + ", " + std::to_string(mine);
		s += ");\n";
		s += "boul.addOrder(\"";
		s += order;
		s += "\");";
		*/

		return s;
	}
	Point getPos() { return pos; }
	void setPos(int i, int y) { pos = Point(i, y); }
	int getTorpe() { return torpe; }
	int getSilence() { return silence; }
	int getSonar() { return sonar; }
	int getMine() { return mine; }
};

#endif // !INFOBOUCLE
