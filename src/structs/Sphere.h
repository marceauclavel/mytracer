#pragma once

#include <istream>
#include "Point.h"

struct Sphere {
	Point pos;
	float r;
};

inline std::istream& operator >> (std::istream& i, Sphere& s) {
	return i >> s.pos >> s.r;
};
