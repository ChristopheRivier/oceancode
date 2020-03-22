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