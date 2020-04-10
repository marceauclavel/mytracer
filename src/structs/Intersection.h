#pragma once

#include "Ray.h"
#include "Vector.h"
#include "Material.h"
#include "Sphere.h"

struct Intersection {
	Ray* iray;
	Vector n;
	Material* mat;
	Sphere* sph;
};
