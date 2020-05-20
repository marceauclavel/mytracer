#include "Ray.h"

Ray::Ray() {
	pos = Vector(0, 0, 0);
	dir = Vector(0, 0, 0);
}

Ray::Ray(Vector npos, Vector ndir) {
	pos = npos;
	dir = ndir;
}
