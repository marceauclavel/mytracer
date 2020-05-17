#pragma once

#include "Point.h"
#include "Vector.h"
#include "Pixel.h"

struct Camera {
	Point pos;
	Vector dir;
	int xOpening, yOpening;
	int xRes, yRes;
	int depth;
	unsigned int nPixels;
	Pixel* screen;
	bool print(const char* ofn);
	Camera();
	Camera(Point pos, Vector dir, int xOpening, int yOpening, int xRes, int yRes, int depth, int nPixels, Pixel* screen);
};
