#pragma once

#include <istream>
#include "Vector.h"

struct Vector {
	float x, y, z;
	void normalize();
	Vector();
	Vector(float, float, float);
	Vector(const Vector&);
	Vector(const Vector*);
	Vector cross(Vector);
	float dot(const Vector);
	float norm();
	void rotate(Vector, float);
	friend Vector operator + (Vector, Vector);
	friend Vector operator * (float, Vector);
	friend Vector operator - (Vector, Vector);
};

inline std::istream& operator >> (std::istream& i, Vector& v) {
	return i >> v.x >> v.y >> v.z;
};

inline std::ostream& operator << (std::ostream& o, Vector& v) {
	return o << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
};

