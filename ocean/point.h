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
		if (x < 15) {
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
		if (y < 15) {
			++y;
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif // !POINT
