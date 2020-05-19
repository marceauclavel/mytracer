#pragma once

#include <istream>
#include "Point.h"
#include "Material.h"
#include "Ray.h"

struct Sphere {
	Point pos;
	float r;
	Material mat;
	int matNb;
	float intersects(Ray);
};

inline std::istream& operator >> (std::istream& i, Sphere& s) {
	return i >> s.pos >> s.r >> s.matNb;
};
