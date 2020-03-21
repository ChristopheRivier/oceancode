#pragma once
#include <iostream>


bool debug = true;
class Tuile {
	char input;
public:
	Tuile() { input = '\0'; }
	void setChar(char c) { input = c; }
	char getChar() { return input; }
	bool isOcean() { return input == '.'; }
};

class Carte {
	int width;
	int height;
	int myId;
	Tuile cart[15][15];
public:
	
	Carte(int w, int h, int i):width(w),height(h),myId(i){}
	void addTuile(int i, int j, char in) {
		cart[i][j].setChar(in);
	}
	void addLine(int i, std::string line) {
		for (int j = 0; j < width; ++j) {
			cart[i][j].setChar(line[j]);
		}
	}
	void printCarte() {
		if (true) {
			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					std::cerr << cart[j][i].getChar();
				}
				std::cerr << std::endl;
			}
		}
	}
};