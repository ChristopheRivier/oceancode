#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#include "point.h"
#include "carte.h"

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
	int width;
	int height;
	int myId;
	
	cin >> width >> height >> myId; cin.ignore();
	Carte ca(width, height, myId);
	for (int i = 0; i < height; i++) {
		string line;
		getline(cin, line);
		ca.addLine(i, line);
	}
	ca.printCarte();
	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;

	cout << "7 7" << endl;

	// game loop
	while (1) {
		int x;
		int y;
		int myLife;
		int oppLife;
		int torpedoCooldown;
		int sonarCooldown;
		int silenceCooldown;
		int mineCooldown;
		cin >> x >> y >> myLife >> oppLife >> torpedoCooldown >> sonarCooldown >> silenceCooldown >> mineCooldown; cin.ignore();
		string sonarResult;
		cin >> sonarResult; cin.ignore();
		string opponentOrders;
		getline(cin, opponentOrders);

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		cout << "MOVE N TORPEDO" << endl;
	}
}