#pragma once

#include <istream>

struct Point {
	float x, y, z;
};

inline std::istream& operator >> (std::istream& i, Point& p) {
	return i >> p.x >> p.y >> p.z;
};
