#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool debug = true;

using namespace std;
#include "point.h"
#include "carte.h"
#include "infoboucle.h"
#include "zoneOpp.h"
#include "action.h"
#include "game.h"

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
		cerr << line << endl;
	}

	// Write an action using cout. DON'T FORGET THE "<< endl"
	// To debug: cerr << "Debug messages..." << endl;
	Point a = ca.getInit();
	cout << a.toString() << endl;
	Game game(debug);
	game.addCarte(ca);
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
		InfoBoucle boul(x, y, myLife, oppLife, torpedoCooldown, sonarCooldown, silenceCooldown, mineCooldown);
		string sonarResult;
		cin >> sonarResult; cin.ignore();
		boul.addSonar(sonarResult);
		string opponentOrders;
		getline(cin, opponentOrders);
		boul.addOrder(opponentOrders);
		game.addBoucle(boul);
		if (debug)
		{
			std::cerr << boul.print() << endl;

			std::cerr << game.getLstPossible().size() << " possible" << endl;
//			game.printLstPossible("call");

		}
		
		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;

		// Write an action using cout. DON'T FORGET THE "<< endl"
		// To debug: cerr << "Debug messages..." << endl;
		
		cout <<  game.getMove()<< endl;

	}
}