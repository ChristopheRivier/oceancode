#ifndef POINT
#define POINT

#include <string>

class Point {
	int x, y;
public:
	Point() :x(0), y(0) {}
	Point(int a, int b):x(a),y(b){}
	std::string toString() { return  std::to_string(x) + " " + std::to_string(y); }
};

#endif // !POINT

