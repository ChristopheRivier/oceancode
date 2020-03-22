#ifndef INFOBOUCLE
#define INFOBOUCLE


#include <string>
#include "point.h"

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
public:
	InfoBoucle(int x, int y, int l, int o, int t, int s, int q, int m):pos(x,y),mylife(l),opplife(o),torpe(t), sonar(s), silence(q),mine(m){}
	void addSonar(std::string s) {
		sonarRes = s;
	}
	void addOrder(std::string o) {
		order = o;
	}
	std::string print() {
		std::string s;
		s = pos.toString() + " " + std::to_string(mylife) + " " + std::to_string(opplife) + " " + std::to_string(torpe) + " " + std::to_string(sonar) + " " + std::to_string(silence) + " " + std::to_string(mine);
		s += "\n";
		s += sonarRes;
		s += "\n";
		s += order;
		return s;
	}
	Point getPos() { return pos; }
};

#endif // !INFOBOUCLE
