#pragma once
#include <iostream>
#include "point.h"

class Tuile {
	char input;
	bool pass = false;
public:
	Tuile() { input = '\0'; }
	void setChar(char c) { input = c; }
	char getChar() { return input; }
	bool isOcean() { return input == '.'; }
	bool isFree() { return !pass && isOcean(); }
	void clearPass() { pass = false; }
	void passer() { pass = true; }
};

class Carte {
	int width;
	int height;
	int myId;
	Tuile cart[15][15];
	Point init;
public:
	Carte() :width(15), height(15), myId(0) {}
	Carte(int w, int h, int i):width(w),height(h),myId(i){}
	void addTuile(int i, int j, char in) {
		cart[i][j].setChar(in);
	}
	void addLine(int i, std::string line) {
		for (int j = 0; j < width; ++j) {
			cart[j][i].setChar(line[j]);
		}
	}
	bool isIsland(Point& p) {
		return !cart[p.x][p.y].isOcean();
	}
	Point getInit() {
		Point a(7, 7);
		//TODO le calcul n’est pas comme je voulais a refaire
		while (isIsland(a))
		{
			if (!a.goN())
				if (!a.goE())
					if (!a.goS())
						a.goW();
		}
		init = a;
		return init;
	}
	bool deplacementPossible(Point p) {
		return cart[p.x][p.y].isFree();
	}
	void printCarte() {
		if (true) {
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					std::cerr << cart[i][j].getChar();
				}
				std::cerr << std::endl;
			}
		}
	}
};