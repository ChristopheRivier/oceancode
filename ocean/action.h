#ifndef ACTION_H
#define ACTION_H

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


class Actions {
	std::string direction;
	Point tir;
	int zoneSonar;
public:
	Actions() { init(); }
	void init() {
		direction = "";
		tir = Point(-1, -1);
		zoneSonar = -1;
	}
	void setDirection(std::string s) { direction = s; }
	void setTir(Point p) { tir = p; }
	void setSonar(int z) { zoneSonar = z; }
	Point getTir() { return tir; }
};

class Action {
public:
	enum typeAction {
		None=-1,
		Silence,
		Move,
		Torpedo,
		Mine,
		Surface
	};

	Action(std::string t) :pos(Point(-1, -1)),type(None) {
		if (t.back() == ' ') {
			t.pop_back();
		}

		if (t.find("MOVE") != std::string::npos) {
			type = Move;
			deplacement = t.back();
		}
		else if (t.find("SILENCE") != std::string::npos) {
			type = Silence;
			deplacement = '?';
		}
		else if (t.find("SURFACE") != std::string::npos) {
			type = Surface;
			std::string i;
			i.push_back(t.back());
			zone = std::stoi(i);
		}
		else if (t.find("TORPEDO") != std::string::npos) {
			type = Torpedo;
			std::vector<std::string> list = split(t, ' ');
			pos = Point(std::stoi(list[1]), std::stoi(list[2]));
		}
		else if (t.find("MINE") != std::string::npos) {
			type = Mine;
		}
	}
	typeAction getType() {
		return type;
	}
	char getDep() { return deplacement; }
	int getZone() { return zone; }
	Point getPos() { return pos; }
private:
	typeAction type;
	char deplacement;
	int zone;
	Point pos;
};

#endif