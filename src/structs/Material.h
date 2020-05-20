#pragma once

#include <istream>
#include "Color.h"

struct Material {
	Color ambient;
	Color diffuse;
	Material();
	Material(Color, Color);
};

inline std::istream& operator >> (std::istream& i, Material& m) {
	return i >> m.ambient >> m.diffuse;
}
