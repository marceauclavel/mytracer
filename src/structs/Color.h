#pragma once

#include <istream>

struct Color {
	int r, g, b;
};

inline std::istream& operator >> (std::istream& i, Color& c) {
	return i >> c.r >> c.g >> c.b;
};
