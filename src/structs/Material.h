#pragma once

#include <istream>
#include "Color.h"

struct Material {
	Color col;
};

inline std::istream& operator >> (std::istream& i, Material& m) {
	return i >> m.col;
}
