#include "pch.h"

#include "../ocean/point.h"
#include "../ocean/carte.h"
#include "../ocean/infoboucle.h"
#include "../ocean/game.h"



Carte initCarte() {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0 , "...............");
	ca.addLine(1 , "...............");
	ca.addLine(2 , ".....xxxx....xx");
	ca.addLine(3 , ".....xxxx....xx");
	ca.addLine(4 , ".............xx");
	ca.addLine(5 , ".............xx");
	ca.addLine(6 , "...............");
	ca.addLine(7 , "...............");
	ca.addLine(8 , ".......x..xx...");
	ca.addLine(9 , "..........xx...");
	ca.addLine(10, "...............");
	ca.addLine(11, "...............");
	ca.addLine(12, ".........xxx...");
	ca.addLine(13, "......xx.xxx...");
	ca.addLine(14, "......xx.xxx...");
	return ca;
}
TEST(TestCaseName, PlacementInit) {
 
	Carte c = initCarte();
	Point p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 7);
	c.addLine(7, "xxxxxxxxxxxxxxx");
	p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 6);
	c.addLine(6, "xxxxxxxxxxxxxxx");
	p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 5);
	// bloque tout le nord
	c.addLine(0, ".......x.......");
	c.addLine(1, ".......x.......");
	c.addLine(2, ".....xxxx....xx");
	c.addLine(3, ".....xxxx....xx");
	c.addLine(4, ".......x.....xx");
	c.addLine(5, ".......x.....xx");
	c.addLine(6, ".......x.......");
	p = c.getInit();
	EXPECT_EQ(p.x, 8);
	EXPECT_EQ(p.y, 0);


}

TEST(TestCaseName, deplacement) {

	Carte c = initCarte();
	Point p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 7);
	InfoBoucle boul(p.x, p.y, 6, 6, 1, 1, 1, 1);
	Game a;
	a.addCarte(c);
	a.addBoucle(boul);
	EXPECT_EQ(a.calculDeplacement(), "N");
	a.modifCarte(6, ".......x.......");
	EXPECT_EQ(a.calculDeplacement(), "E");
	a.modifCarte(7, "........x......");
	a.modifCarte(8, "..........xx...");
	EXPECT_EQ(a.calculDeplacement(), "S");
	a.modifCarte(8, ".......x..xx...");
	EXPECT_EQ(a.calculDeplacement(), "W");
}

TEST(TestCaseName, deplacementposition) {

	Carte c = initCarte();
	Point p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 7);
	InfoBoucle boul(p.x, p.y, 6, 6, 1, 1, 1, 1);
	Game a;
	a.addCarte(c);
	a.addBoucle(boul);
	EXPECT_EQ(a.calculDeplacement(), "N");
//si je viens du nord
	c.position(Point(7, 6));
	a.addCarte(c);
	EXPECT_EQ(a.calculDeplacement(), "E");
	c.position(Point(8, 7));
	a.addCarte(c);
	a.modifCarte(8, "..........xx...");
	EXPECT_EQ(a.calculDeplacement(), "S");
	c.position(Point(7, 8));
	a.addCarte(c);
	EXPECT_EQ(a.calculDeplacement(), "W");
}


TEST(TestCaseName, testPossibleZone) {

	std::vector<Point> lst;
	lst.push_back(Point(1, 1));
	lst.push_back(Point(5, 1));
	lst.push_back(Point(10, 1));
	lst.push_back(Point(1, 5));
	lst.push_back(Point(5, 5));
	lst.push_back(Point(10, 5));
	lst.push_back(Point(1, 10));
	lst.push_back(Point(5, 10));
	lst.push_back(Point(10, 10));
	Game game;
	game.setLstPossible(lst);
	EXPECT_EQ(game.getLstPossible().size(), 9);

	game.cleanPossible(1);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.cleanPossible(2);
	EXPECT_EQ(game.getLstPossible().size(), 0);
	game.setLstPossible(lst);
	game.cleanPossible(2);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);

	game.cleanPossible(3);
	EXPECT_EQ(game.getLstPossible().size(), 1);

	game.cleanPossible(3);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(3);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(4);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(5);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(6);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(7);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(8);
	EXPECT_EQ(game.getLstPossible().size(), 1);
	game.setLstPossible(lst);
	game.cleanPossible(9);
	EXPECT_EQ(game.getLstPossible().size(), 1);


}


// test given entry from opponent
TEST(TestCaseOposant, entreeOpposant) {

	Carte c = initCarte();
	Point p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 7);
	InfoBoucle boul(p.x, p.y, 6, 6, 1, 1, 1, 1);
	boul.addOrder("NA");
	Game a;
	a.addCarte(c);
	a.addBoucle(boul);
	EXPECT_EQ(a.getLastDeplacement(), "");
	boul.addOrder("MOVE S");
	a.addBoucle(boul);

	EXPECT_EQ(a.getLastDeplacement(), "S");

	boul.addOrder("MOVE N");
	a.addBoucle(boul);

	EXPECT_EQ(a.getLastDeplacement(), "N");

	boul.addOrder("MOVE N|TORPEDO 3 5");
	EXPECT_EQ(a.getLastDeplacement(), "N");
	boul.addOrder("TORPEDO 3 5|MOVE N");
	EXPECT_EQ(a.getLastDeplacement(), "N");

}

TEST(TestCaseOposant, calculCarre) {
	Carte c = initCarte();
	Point p = c.getInit();
	EXPECT_EQ(p.x, 7);
	EXPECT_EQ(p.y, 7);
	InfoBoucle boul(p.x, p.y, 6, 6, 1, 1, 1, 1);
	boul.addOrder("MOVE S");
	Game a;
	a.addCarte(c);
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 2);
	
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 3);

	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 4);

	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 5);

	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 6);

	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 6);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 6);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 6);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 6);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 6);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 7);
	boul.addOrder("MOVE N|");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 8);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 9);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 9);
	EXPECT_EQ(a.getLargeur(), 2);
	boul.addOrder("MOVE W");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 9);
	EXPECT_EQ(a.getLargeur(), 2);
	boul.addOrder("MOVE W");
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 9);
	EXPECT_EQ(a.getLargeur(), 3);

}

TEST(TestCaseOposant, calculPossible) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0, "xxxxxxxxxxxxxxx");
	ca.addLine(1, "x.............x");
	ca.addLine(2, "x.....xxxx..xxx");
	ca.addLine(3, "x.....xxxx....x");
	ca.addLine(4, "x.............x");
	ca.addLine(5, "x.............x");
	ca.addLine(6, "x.............x");
	ca.addLine(7, "x.............x");
	ca.addLine(8, "x.......x..xx.x");
	ca.addLine(9, "x..........xx.x");
	ca.addLine(10, "x.............x");
	ca.addLine(11, "x.............x");
	ca.addLine(12, "x.........xx..x");
	ca.addLine(13, "x.x..........xx");
	ca.addLine(14, "x.xxxxxxxxxxxxx");
	Point p = ca.getInit();
	InfoBoucle boul(10, 2, 6, 6, 1, 1, 1, 1);
	boul.addOrder("MOVE N");
	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	for (int i = 0; i < 12; ++i) {
		boul.addOrder("MOVE N");
		a.addBoucle(boul);
	}
	EXPECT_EQ(a.getHauteur(), 14);
	for (int i = 0; i < 12; ++i) {
		boul.addOrder("MOVE E");
		a.addBoucle(boul);
	}
	EXPECT_EQ(a.getLargeur(), 13);
	ca.printCarte();
	a.calculDesPossible();
	EXPECT_EQ(a.getLstPossible().size(), 1);
	boul.setPos(1, 1);
	a.addBoucle(boul);
	EXPECT_TRUE((a.isNear(boul.getPos())).x == -1);
}

TEST(TestCaseOposant, getMove ) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0, "xxxxxxxxxxxxxxx");
	ca.addLine(1, "x.............x");
	ca.addLine(2, "x.....xxxx..xxx");
	ca.addLine(3, "x.....xxxx....x");
	ca.addLine(4, "x.............x");
	ca.addLine(5, "x.............x");
	ca.addLine(6, "x.............x");
	ca.addLine(7, "x.............x");
	ca.addLine(8, "x.......x..xx.x");
	ca.addLine(9, "x..........xx.x");
	ca.addLine(10, "x.............x");
	ca.addLine(11, "x.............x");
	ca.addLine(12, "x.........xx..x");
	ca.addLine(13, "x.x..........xx");
	ca.addLine(14, "x.xxxxxxxxxxxxx");
	Point p = ca.getInit();
	InfoBoucle boul(10, 2, 6, 6, 0, 1, 1, 1);
	boul.addOrder("MOVE N");
	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	for (int i = 0; i < 12; ++i) {
		boul.addOrder("MOVE N");
		a.addBoucle(boul);
	}
	EXPECT_EQ(a.getHauteur(), 14);
	for (int i = 0; i < 12; ++i) {
		boul.addOrder("MOVE E");
		a.addBoucle(boul);
	}
	EXPECT_EQ(a.getLargeur(), 13);
	ca.printCarte();
	a.calculDesPossible();
	EXPECT_EQ(a.getLstPossible().size(), 1);
	std::string s = a.getMove();
	EXPECT_EQ(s, "MOVE N|TORPEDO 13 1");

}

TEST(TestCaseOposant, CalculSilence) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0, "...............");
	ca.addLine(1, "xxxxxx.xxxxxxxx");
	ca.addLine(2, "xxxxxx.xxxxxxxx");
	ca.addLine(3, ".xxxxx.xxxxxxxx");
	ca.addLine(4, "xxxxxx.xxxxxxxx");
	ca.addLine(5, ".xxxxx..xxxxxx.");
	ca.addLine(6, ".xxxxxxxxxxxxx.");
	ca.addLine(7, ".xxx.xxxxxxxxxx");
	ca.addLine(8, "..xx.xxxxxxxxxx");
	ca.addLine(9, "xxxxxxxxxxxxxxx");
	ca.addLine(10, "xxxxxxxxxxxxxxx");
	ca.addLine(11, "xxxxxxxxxxxxxxx");
	ca.addLine(12, "xxxxxxxxxxxxxxx");
	ca.addLine(13, "xxxxxxxxxxxxxxx");
	ca.addLine(14, "xxxxxxxxxxxxxxx");
	Point p = ca.getInit();
	InfoBoucle boul(0, 0, 6, 6, 0, 1, 1, 1);
	boul.addOrder("MOVE E");

	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	a.getMove();
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	EXPECT_EQ(a.getLstPossible().size(), 1);
	boul.addOrder("SILENCE");
	a.addBoucle(boul);
	EXPECT_EQ(a.getLstPossible().size(), 1);

}

TEST(TestCaseTorpille, TorpilleOne) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0, "...............");
	ca.addLine(1, ".......xx......");
	ca.addLine(2, ".xx....xx......");
	ca.addLine(3, ".xx............");
	ca.addLine(4, "...............");
	ca.addLine(5, ".xxx........xx.");
	ca.addLine(6, ".xxx........xx.");
	ca.addLine(7, ".xxx...........");
	ca.addLine(8, "..xx...........");
	ca.addLine(9, "...............");
	ca.addLine(10, "...............");
	ca.addLine(11, ".......xx......");
	ca.addLine(12, ".......xx......");
	ca.addLine(13, "...xx..........");
	ca.addLine(14, "...xx..........");
	Point p = ca.getInit();
	InfoBoucle boul(12, 8, 6, 6, 0, 1, 1, 1);
	boul.addOrder("MOVE E");

	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);

	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 4 3 | MOVE E ");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 6 5 | MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE W");
	a.addBoucle(boul);
	boul.addOrder("MOVE W");
	a.addBoucle(boul);
	boul.addOrder("MOVE W");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 3 2 | MOVE W");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 2 9 | MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 3 12 | MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 2 13 | MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 4 9 | MOVE W");
	a.addBoucle(boul);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	boul.addOrder("MOVE W");
	a.addBoucle(boul);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 2 11 | MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	boul.addOrder("TORPEDO 5 6 | MOVE E");
	a.addBoucle(boul);

	EXPECT_EQ(a.getHauteur(), 13);
	EXPECT_EQ(a.getLargeur(), 9);


	a.calculDesPossible();
	EXPECT_EQ(a.getLstPossible().size(), 1);

	std::string s = a.getMove();
	EXPECT_EQ(s, "MOVE W|TORPEDO 8 8");

}

TEST(TestCaseTorpille, TorpilleTwo) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0, "...............");
	ca.addLine(1, ".......xx......");
	ca.addLine(2, ".xx....xx......");
	ca.addLine(3, ".xx............");
	ca.addLine(4, "...............");
	ca.addLine(5, ".xxx........xx.");
	ca.addLine(6, ".xxx........xx.");
	ca.addLine(7, ".xxx........xx.");
	ca.addLine(8, "..xx...xx...xx.");
	ca.addLine(9, "..xx...........");
	ca.addLine(10, "...............");
	ca.addLine(11, ".....xxxx......");
	ca.addLine(12, ".....xxxx......");
	ca.addLine(13, "...xxxxxxxxxxxx");
	ca.addLine(14, "...xxxxxxxxxxxx");
	Point p = ca.getInit();
	InfoBoucle boul(12, 7, 6, 6, 0, 0, 0, 1);
	boul.addOrder("MOVE E");

	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	EXPECT_EQ(a.getHauteur(), 1);
	EXPECT_EQ(a.getLargeur(), 2);


	a.calculDesPossible();
	EXPECT_EQ(a.getLstPossible().size(), 147);

	std::string s = a.getMove();
	EXPECT_EQ(s, "SILENCE W 1");

}
TEST(TestCaseTorpille, TorpilleThree) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0,  "............xx.");
	ca.addLine(1,  "............xx.");
	ca.addLine(2,  "............xx.");
	ca.addLine(3,  "...............");
	ca.addLine(4,  "...............");
	ca.addLine(5,  "...............");
	ca.addLine(6,  "...........xx..");
	ca.addLine(7,  "...........xx..");
	ca.addLine(8,  "...............");
	ca.addLine(9,  "...............");
	ca.addLine(10, "...xxx.........");
	ca.addLine(11, "...xxx.........");
	ca.addLine(12, "...xxx......xx.");
	ca.addLine(13, "............xx.");
	ca.addLine(14, "...............");

	Point p = ca.getInit();
	InfoBoucle boul(7, 4, 6, 6, 0, 1, 1, 1);
	boul.addOrder("MOVE E");

	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);

	EXPECT_EQ(a.getHauteur(), 3);
	EXPECT_EQ(a.getLargeur(), 2);


	a.calculDesPossible();
	EXPECT_EQ(a.getLstPossible() .size(), 147);

	std::string s = a.getMove();
	EXPECT_EQ(s, "MOVE N SILENCE");

	boul.addOrder("SURFACE 6");
	a.addBoucle(boul);
	EXPECT_EQ(a.getLstPossible().size(), 17);

}


TEST(TestCaseTorpille, TorpilleFor) {
	Carte ca(15, 15, 0);

	ca.addLine(0,  "...............");
	ca.addLine(1,  ".......xx......");
	ca.addLine(2,  ".......xx......");
	ca.addLine(3,  ".........xxxx..");
	ca.addLine(4,  ".........xxxx..");
	ca.addLine(5,  ".xx...xx.xxx...");
	ca.addLine(6,  ".xx...xx.......");
	ca.addLine(7,  "...........xx..");
	ca.addLine(8,  "...........xx..");
	ca.addLine(9,  "...............");
	ca.addLine(10, ".......xx......");
	ca.addLine(11, ".......xx......");
	ca.addLine(12, "...............");
	ca.addLine(13, "...............");
	ca.addLine(14, "...............");

	Point p = ca.getInit();
	InfoBoucle boul(7, 7, 6, 6, 3, 4, 6, -1);
	boul.addOrder("NA");

	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	InfoBoucle boul1(8, 7, 6, 6, 2, 4, 6, -1);
	boul.addOrder("SURFACE 7");
	a.addBoucle(boul1);
	boul1 = InfoBoucle(8, 6, 6, 6, 1, 4, 6, -1);
	boul.addOrder("MOVE N");
	a.addBoucle(boul1);
	boul1 = InfoBoucle(8, 5, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE N");
	a.addBoucle(boul1);
	std::string s = a.getMove();
	EXPECT_EQ(s, "MOVE N|TORPEDO 4 5");

}
TEST(TestCaseCG, OutsideMap) {
	Carte ca(15, 15, 0);

	ca.addLine(0, "...........xx..");
	ca.addLine(1, "...........xx..");
	ca.addLine(2, "...............");
	ca.addLine(3, "xxxxx....xxxx..");
	ca.addLine(4, "xxxxx...xxxxx..");
	ca.addLine(5, "xxx.....xxxx...");
	ca.addLine(6, "........xxx....");
	ca.addLine(7, ".....xx.xx.xx..");
	ca.addLine(8, ".....xx.xx.xx..");
	ca.addLine(9, "...............");
	ca.addLine(10, ".......xx......");
	ca.addLine(11, ".......xx......");
	ca.addLine(12, "............xx.");
	ca.addLine(13, "............xx.");
	ca.addLine(14, "...............");

	InfoBoucle boul(7, 7, 6, 6, 3, 4, 6, -1);
	boul.addOrder("NA");
	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);

	std::string s = a.getMove();
	boul = InfoBoucle(7, 6, 6, 6, 2, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);

	boul = InfoBoucle(7, 6, 6, 6, 2, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);

	boul = InfoBoucle(7, 5, 6, 6, 1, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);

	boul = InfoBoucle(7, 4, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(7, 3, 6, 6, 3, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(7, 2, 6, 6, 2, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(7, 1, 6, 6, 1, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(7, 0, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(8, 0, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(9, 0, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(10, 0, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(10, 1, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(10, 2, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(11, 2, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(12, 2, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 2, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 3, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 4, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 5, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 6, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 7, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 8, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 9, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 10, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 11, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(14, 11, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(14, 12, 6, 6, 0, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(14, 13, 6, 4, 3, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(14, 14, 6, 4, 2, 4, 6, -1);
	boul.addOrder("MOVE E");
	a.addBoucle(boul);
	boul = InfoBoucle(13, 14, 6, 4, 1, 4, 6, -1);
	boul.addOrder("MOVE N");
	a.addBoucle(boul);
	s = a.getMove();
	EXPECT_EQ(s, "MOVE W TORPEDO");

}

TEST(TestCaseOpposant, touchecoule) {
	Carte ca(15, 15, 0);
	std::string line;

	ca.addLine(0, "............xx.");
	ca.addLine(1, "............xx.");
	ca.addLine(2, "............xx.");
	ca.addLine(3, "...............");
	ca.addLine(4, "...............");
	ca.addLine(5, "...............");
	ca.addLine(6, "...........xx..");
	ca.addLine(7, "...........xx..");
	ca.addLine(8, "...............");
	ca.addLine(9, "...............");
	ca.addLine(10, "...xxx.........");
	ca.addLine(11, "...xxx.........");
	ca.addLine(12, "...xxx......xx.");
	ca.addLine(13, "............xx.");
	ca.addLine(14, "...............");

	Point p = ca.getInit();
	InfoBoucle boul(7, 4, 6, 6, 0, 1, 1, 1);
	boul.addOrder("MOVE E");

	Game a;
	a.addCarte(ca);
	a.addBoucle(boul);
	a.getMove();
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	a.getMove();

	EXPECT_EQ(a.getHauteur(), 3);
	EXPECT_EQ(a.getLargeur(), 2);


	a.calculDesPossible();
	EXPECT_EQ(a.getLstPossible().size(), 147);

	std::string s = a.getMove();
	EXPECT_EQ(s, "MOVE N SILENCE");

	boul.addOrder("SURFACE 6");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);

	boul = InfoBoucle(13, 10, 6, 6, 0, 1, 1, 1);
	boul.addOrder("MOVE S");
	a.addBoucle(boul);
	// tir en 10 11
	a.getMove();

	// pas toucher 
	boul = InfoBoucle(13, 10, 6, 6, 0, 1, 1, 1);
	boul.addOrder("SURFACE 9");
	a.addBoucle(boul);
	EXPECT_EQ(a.getLstPossible().size(), 8);

	// tir en 11 12
	a.getMove();
	boul = InfoBoucle(13, 10, 6, 5, 0, 1, 1, 1);
	boul.addOrder("SURFACE 9");
	a.addBoucle(boul);

	EXPECT_EQ(a.getLstPossible().size(), 3);
	a.getMove();
	boul = InfoBoucle(13, 10, 6, 3, 0, 1, 1, 1);
	boul.addOrder("SURFACE 9");
	a.addBoucle(boul);

	EXPECT_EQ(a.getLstPossible().size(), 1);

}

TEST(TestCaseCG, Recursion) {
	Carte ca(15, 15, 0);

	ca.addLine(0, ".xxxxxxxxxxxx..");
	ca.addLine(1, "xxxxxxxxxxxxx..");
	ca.addLine(2, "...............");
	ca.addLine(3, "xxxxx....xxxx..");
	ca.addLine(4, "xxxxx...xxxxx..");
	ca.addLine(5, "xxx.....xxxx...");
	ca.addLine(6, "........xxx....");
	ca.addLine(7, ".....xx.xx.xx..");
	ca.addLine(8, ".....xx.xx.xx..");
	ca.addLine(9, "...............");
	ca.addLine(10, ".......xx......");
	ca.addLine(11, ".......xx......");
	ca.addLine(12, "............xx.");
	ca.addLine(13, "............xx.");
	ca.addLine(14, "...............");

	ca.position(Point(0, 0));
	EXPECT_EQ(ca.calcDeplacement(0,Point(1,0),"E"), -100.0);

	ca.addLine(0, "..xxxxxxxxxxx..");
	double a = -100 / 3;
	a += -100 / 3;
	a+= -100 / 3;
	EXPECT_EQ(ca.calcDeplacement(0, Point(1, 0), "E"), a);
	ca.addLine(0, "...xxxxxxxxxx..");
	EXPECT_EQ(ca.calcDeplacement(0, Point(1, 0), "E"), -55.555555);

	ca.position(Point(0, 0));
	ca.position(Point(0, 0));
	ca.position(Point(0, 0));

}