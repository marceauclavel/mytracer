#pragma once

#include "Vector.h"
#include "Vector.h"

struct Ray {
	Vector pos;
	Vector dir;
	Ray();
	Ray(Vector, Vector);
};
