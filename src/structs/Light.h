#pragma once

#include <istream>

#include "Point.h"
#include "Color.h"

struct Light {
	Point pos;
	Color col;
};

inline std::istream& operator >> (std::istream& i, Light& l){
	return i >> l.pos >> l.col;
};
