#include "Vector.h"

#include <cmath>
#include <iostream>

void Vector::normalize() {
	float norm = this->norm();
	x = x / norm;
	y = y / norm;
	z = z / norm;
}

Vector::Vector(){
	x = 0.;
	y = 0.;
	z = 0.;
}

Vector::Vector(float nx, float ny, float nz) {
	x = nx;
	y = ny;
	z = nz;
}
Vector Vector::cross(Vector v) {
	float nx = y * v.z - z * v.y;
	float ny = z * v.x - x * v.z;
	float nz = x * v.y - y * v.x;
	return Vector(nx, ny, nz);
}

float Vector::norm() {
	return std::sqrt(x * x + y * y + z * z);
}

Vector::Vector(const Vector& v){
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector::Vector(const Vector* v){
	x = v->x;
	y = v->y;
	z = v->z;
}

void Vector::rotate(Vector dir, float angle){
	Vector rotVector = this;
	rotVector = cos(angle) * rotVector;
	rotVector = rotVector + sin(angle) * (dir.cross(this));
	rotVector = rotVector + (dir.dot(this) * (1 - cos(angle)))  * dir;
	*this = rotVector;
}

float Vector::dot(Vector v) {
	return x * v.x + y * v.y + z * v.z;
}

Vector operator + (const Vector u, const Vector v) {
	return Vector(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector operator * (const float a, const Vector v) {
	return Vector(a * v.x, a * v.y, a * v.z);
}

Vector operator - (const Vector p, const Vector q) {
	return Vector(p.x - q.x, p.y - q.y, p.z - q.z);
}
