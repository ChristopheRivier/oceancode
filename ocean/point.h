#ifndef POINT
#define POINT

#include <string>

class Point {
public:
	int x, y;

	Point() :x(0), y(0) {}
	Point(int a, int b):x(a),y(b){}
	std::string toString() { return  std::to_string(x) + " " + std::to_string(y); }
	Point getN() {
		Point ret(this->x, this->y);
		ret.goN();
		return ret;
	}
	Point getS() {
		Point ret(this->x, this->y);
		ret.goS();
		return ret;
	}
	Point getE() {
		Point ret(this->x, this->y);
		ret.goE();
		return ret;
	}
	Point getW() {
		Point ret(this->x, this->y);
		ret.goW();
		return ret;
	}

	bool go(char w) {
		switch (w) {
		case 'N':
			return goN();
		case 'S':
			return goS();
		case 'E':
			return goE();
		case 'W':
			return goW();
		case '?':
			//in that case we will do the test after
			return true;
		}
		return false;
	}
	bool goN() {
		if (y > 0) {
			--y;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool goE() {
		if (x < 14) {
			++x;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool goW() {
		if (x > 0) {
			--x;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool goS() {
		if (y < 14) {
			++y;
			return true;
		}
		else
		{
			return false;
		}
	}
	bool N() {
		if (y > 0) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool E() {
		if (x < 14) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool W() {
		if (x > 0) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool S() {
		if (y < 14) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(const Point& a) {
		return this->x == a.x && this->y == a.y;
	}
	bool operator!=(const Point& a) {
		return this->x != a.x || this->y != a.y;
	}
};

#endif // !POINT

