#pragma once

#include <istream>

struct Vector {
	float x, y, z;
	void normalize();
	Vector();
	Vector(float, float, float);
	Vector cross(Vector);
	friend Vector operator + (Vector, Vector);
	friend Vector operator * (float, Vector);
};

inline std::istream& operator >> (std::istream& i, Vector& v) {
	return i >> v.x >> v.y >> v.z;
};

inline std::ostream& operator << (std::ostream& o, Vector& v) {
	return o << "Vector(" << v.x << ", " << v.y << ", " << v.z << ")";
};

