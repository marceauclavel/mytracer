#include "Vector.h"
#include <cmath>
#include <iostream>

void Vector::normalize() {
	float norm = x * x + y * y + z * z;
	norm = std::sqrt(norm);
	x = x / norm;
	y = y / norm;
	z = z / norm;
}

Vector::Vector(){
	x = 0.;
	y = 0.;
	z = 0.;
}

Vector::Vector(float x, float y, float z) {
	std::cout << "initialising a vector to " << x << " " << y << " " << z << " using the constructor Vector(float, float, float)" << std::endl;
	x = x;
	y = y;
	z = z;
}
Vector Vector::cross(Vector v) {
	float nx = y * v.z - z * v.y;
	float ny = z * v.x - x * v.z;
	float nz = x * v.y - y * v.x;
	std::cout << "crossing" << x << " " << y << " " << z << std::endl;
	return Vector(nx, ny, nz);
}
