#ifndef ZONE_OPP
#define ZONE_OPP
#include <string>

class ZoneOpp {
	//!position x
	int px=0;
	//!position y
	int py=0;
	//!largeur de la zone
	int tx=1;
	//!hauteur de la zone
	int ty = 1;
public:
	void init() {
		px = py = 0;
		tx = ty = 1;
	}
	int getHauteur() { return ty; }
	int getLargeur() { return tx; }
	Point getPosition() { return Point(px, py); }
	void move(std::string m) {
		if (m.compare("N")==0) {
			if (py == 0) {
				ty++;
			}
			else if (py > 0) {
				py--;
			}
		}
		else if (m.compare("S")==0) {
			py++;
			if (py == ty) {
				ty++;
			}
		}
		else if (m.compare("W")==0) {
			if (px == 0) {
				tx++;
			}
			else if (px > 0) {
				px--;
			}
		}
		else if (m.compare("E")==0) {
			px++;
			if (px == tx) {
				tx++;
			}
		}
	}

};

#endif // !ZONE_OPP
