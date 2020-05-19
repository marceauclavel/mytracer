#include "Camera.h"
#include <math.h>
#include <ostream>

#define PI 3.14159265

void Camera::setupScreen() {
	Ray* ray = NULL;
	ray->pos = pos;
	Vector yDir = Vector(0, 0, 1);
	Vector xDir = dir.cross(yDir);
	float xOpeningRad = xOpening * PI / 180;
	float yOpeningRad = yOpening * PI / 180;
	float xAngleStep = xOpeningRad / xRes;
	float yAngleStep = yOpeningRad / yRes;
	float xAngle = 1. * (xRes / 2) * xAngleStep;
	float yAngle = 1. * (yRes / 2) * yAngleStep;
	ray->dir.rotate(yDir, xAngle);
	ray->dir.rotate(xDir, yAngle);
	screen[0].pray.pos = ray->pos;
	screen[0].pray.dir = ray->dir;
	for (int i = 0; i < xRes; ++i) {
		for (int j = 1; j < yRes; ++j) {
			ray->dir.rotate(yDir, -1 * xAngleStep);
			ray->dir.rotate(xDir, -1 * yAngleStep);
			screen[i + xRes * j].pray.pos = ray->pos;
			screen[i + xRes * j].pray.dir = ray->dir;
		}
	}
}

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
