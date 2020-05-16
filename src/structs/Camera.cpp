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

Camera::Camera(Point npos, Vector ndir, int nxOpening, int nyOpening, int nxRes, int nyRes, int ndepth, int nnPixels, Pixel* nscreen) {
	pos = npos;
	dir = ndir;
	xOpening = nxOpening;
	yOpening = nyOpening;
	xRes = nxRes;
	yRes = nyRes;
	depth = ndepth;
	nPixels = nnPixels;
	screen = nscreen;
}
