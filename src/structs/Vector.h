#pragma once

#include <istream>

struct Vector {
	float x, y, z;
};

inline std::istream& operator >> (std::istream& i, Vector& v) {
	return i >> v.x >> v.y >> v.z;
};
