#include "Camera.h"
#include <ostream>

Camera::Camera() {
	pos = Point();
	dir = Vector();
	xOpening = 0;
	yOpening = 0;
	xRes = 0;
	yRes = 0;
	depth = 0;
	nPixels = 0;
	screen = nullptr;
}
Camera::Camera(Point pos, Vector dir, int xOpening, int yOpening, int xRes, int yRes, int depth, int nPixels, Pixel* screen) {
	pos = pos;
	dir = dir;
	xOpening = xOpening;
	yOpening = yOpening;
	xRes = xRes;
	yRes = yRes;
	depth = depth;
	nPixels = nPixels;
	screen = screen;
}
