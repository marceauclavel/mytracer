#include "Point.h"
#include "Vector.h"
#include "Pixel.h"

struct Camera {
	Point pos;
	Vector dir;
	int xOpening, yOpening;
	float xRes, yRes;
	int depth;
	int nPixels;
	Pixel* screen;
	Camera();
	bool print(const char* ofn);
}
