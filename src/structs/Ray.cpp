#include "Ray.h"

Ray::Ray() {
	pos = Point(0, 0, 0);
	dir = Vector(0, 0, 0);
}

Ray::Ray(Point npos, Vector ndir) {
	pos = npos;
	dir = ndir;
}
