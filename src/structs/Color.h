#pragma once

#include <iostream>

struct Color {
	int r, g, b;
	Color();
	Color(const int, const int, const int);
	Color(const int);
	Color(Color&);
};

inline std::istream& operator >> (std::istream& i, Color& c) {
	return i >> c.r >> c.g >> c.b;
};

inline std::ostream& operator << (std::ostream& o, Color& c){
	return o << "Color(" << c.r<<", " << c.g<< ", " << c.b << ")";
}
