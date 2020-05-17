#include "Color.h"

Color::Color() {
	r = 255;
	g = 255;
	b = 255;
}

Color::Color(int nr, int ng, int nb){
	r = nr;
	g = ng;
	b = nb;
}

Color::Color(Color& c){
	r = c.r;
	g = c.g;
	b = c.g;
}
