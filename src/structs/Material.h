#pragma once

#include <istream>
#include "Color.h"

struct Material {
	Color col;
	Material();
	Material(Color);
};

inline std::istream& operator >> (std::istream& i, Material& m) {
	return i >> m.col;
}
