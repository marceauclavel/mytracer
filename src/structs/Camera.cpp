#include "Camera.h"
#include <math.h>
#include <ostream>

#define PI M_PI

void Camera::setupScreen() {
	dir.normalize();
	Ray ray(pos, dir);
	Vector middleDir = dir;
	Vector unitZ(0, 0, 1);
	Vector xDir = dir.cross(unitZ);
	xDir.normalize();
	Vector yDir = xDir.cross(dir);
	float xOpeningRad = xOpening * PI / 180.;
	float yOpeningRad = yOpening * PI / 180.;
	float xAngleStep = xOpeningRad / xRes;
	float yAngleStep = yOpeningRad / yRes;
	for (int j = 0; j < yRes; ++j) {
		for (int i = 0; i < xRes; ++i) {
			screen[i + xRes * j].pray.pos = ray.pos;
			screen[i + xRes * j].pray.dir = middleDir;
			screen[i + xRes * j].pray.dir.rotate(xDir, -1 * (j - yRes / 2) * yAngleStep);
			screen[i + xRes * j].pray.dir.rotate(yDir, -1 * (i - xRes / 2) * xAngleStep);
		}
	}
}

Camera::Camera() {
	pos = Vector();
	dir = Vector();
	xOpening = 0;
	yOpening = 0;
	xRes = 0;
	yRes = 0;
	depth = 0;
	nPixels = 0;
	screen = nullptr;
}

Camera::Camera(Vector npos, Vector ndir, int nxOpening, int nyOpening, int nxRes, int nyRes, int ndepth, int nnPixels, Pixel* nscreen) {
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
