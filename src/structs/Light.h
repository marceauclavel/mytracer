#pragma once

#include <istream>

#include "Vector.h"
#include "Color.h"

struct Light {
	Vector pos;
	Color col;
};

inline std::istream& operator >> (std::istream& i, Light& l){
	return i >> l.pos >> l.col;
};
