#include "Sphere.h"
#include <iostream>

#include <cmath>

float Sphere::intersects(Ray iray){
	// l is the vector from the position of the ray to the center of the sphere
	Vector l = Vector(pos.x - iray.pos.x, pos.y - iray.pos.y, pos.z - iray.pos.z);
	// tca is the projection of l on the direction od the ray
	float tca = l.dot(iray.dir);
	// if tca is negative, it means that the sphere is in the opposite side of the ray
	if (tca < 0) return -1;
	// d2 is the distance between the ray and the center of the sphere (according to pythagorean theorem)
	float d2 = l.dot(l) - tca * tca;
	// if d2 > r*r it means that the ray is hitting the sphere
	if (d2 > r*r) return -1;
	return tca - std::sqrt(r*r - d2);
}
