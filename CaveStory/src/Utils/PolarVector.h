#pragma once
#include "units.h"
#include "Vector2d.h"

template <typename T>
struct PolarVector {
	PolarVector(const T& length, units::Degrees degree):
		length_(length), degree_(degree){}
	void radian() { return units::degreesToRadians(degree_); }
	void setAngle(units::Degrees degree) { degree_ = degree; }
	T xLen() { return length_ * units::cos(degree_); }
	T yLen() { return length_ * units::sin(degree_); }
	operator Vector2D<T>() {
		return Vector2D<T>(xLen(), yLen());
	}
	T length_;
	units::Degrees degree_;
};