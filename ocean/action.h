#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "point.h"

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

#endif