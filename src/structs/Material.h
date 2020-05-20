#pragma once

#include <istream>
#include "Color.h"

struct Material {
	Color ambient;
	Color diffuse;
	Color specular;
	float shininess;
	Material();
	Material(Color, Color, Color, float);
};

inline std::istream& operator >> (std::istream& i, Material& m) {
	return i >> m.ambient >> m.diffuse >> m.specular >> m.shininess;
}
