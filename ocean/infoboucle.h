#ifndef INFOBOUCLE
#define INFOBOUCLE


#include <string>
#include "point.h"
#include <sstream>

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

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
	std::string moveOpp;
	int surface;
public:
	InfoBoucle(int x, int y, int l, int o, int t, int s, int q, int m):pos(x,y),mylife(l),opplife(o),torpe(t), sonar(s), silence(q),
		mine(m), surface(-1){}
	void addSonar(std::string s) {
		sonarRes = s;
	}
	void addOrder(std::string o) {
		order = o;
		//init variable
		moveOpp = "";
		surface = -1;
		std::vector<std::string> list = split(o, '|');
		for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it) {
			if ((*it).find("MOVE") != std::string::npos) {
				if ((*it).back() == ' ' ) {
					(*it).pop_back();
				}			
				moveOpp = (*it).back();
			}
			if ((*it).find("SURFACE") != std::string::npos) {
				if ((*it).back() == ' ') {
					(*it).pop_back();
				}
				surface = std::stoi(std::to_string((*it).back()));
			}

		}
	}
	int getSurface() {
		return surface;
	}
	std::string getMove() {
		return moveOpp;
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
	void setPos(int i, int y) { pos = Point(i, y); }
	int getTorpe() { return torpe; }
};

#endif // !INFOBOUCLE
