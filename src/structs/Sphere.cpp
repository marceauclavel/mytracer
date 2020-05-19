#include "Sphere.h"
#include <iostream>

#include <cmath>

int Sphere::intersects(Ray iray){
	Vector l = Vector(pos.x - iray.pos.x, pos.y - iray.pos.y, pos.z - iray.pos.z);
	//std::cout << l << std::endl;
	//std::cout << l << iray.dir << std::endl;
	float tca = l.dot(iray.dir);
	if (tca < 0) return -1;
	float d2 = l.dot(l) - tca * tca; 
	if (d2 > r*r) return -1;
	//float thc = std::sqrt(r - d2);
	//return (tca < thc)?(tca + thc):(tca - thc);
	return 1;
}
