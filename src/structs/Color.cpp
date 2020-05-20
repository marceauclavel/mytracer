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
	b = c.b;
}

Color operator * (float ratio, Color col){
	Color nCol;
	nCol.r = ratio * col.r;
	nCol.g = ratio * col.g;
	nCol.b = ratio * col.b;
	return nCol;
}

Color operator + (Color cola, Color colb) {
	Color nCol;
	nCol.r = cola.r + colb.r;
	nCol.g = cola.g + colb.g;
	nCol.b = cola.b + colb.b;
	return nCol;
}
