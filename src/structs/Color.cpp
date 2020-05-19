#include "Color.h"

Color::Color() {
	r = 255;
	g = 255;
	b = 255;
}

Color::Color(const int nr, const int ng, const int nb){
	r = nr;
	g = ng;
	b = nb;
}

Color::Color(int nv) {
	r = nv;
	g = nv;
	b = nv;
}

Color::Color(Color& c){
	r = c.r;
	g = c.g;
	b = c.g;
}
