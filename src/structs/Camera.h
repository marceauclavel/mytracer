#pragma once

#include "Vector.h"
#include "Pixel.h"

struct Camera {
	Vector pos;
	Vector dir;
	int xOpening, yOpening;
	int xRes, yRes;
	int depth;
	unsigned int nPixels;
	Pixel* screen;
	bool print(const char* ofn);
	void setupScreen();
	Camera();
	Camera(Vector pos, Vector dir, int xOpening, int yOpening, int xRes, int yRes, int depth, int nPixels, Pixel* screen);
};
