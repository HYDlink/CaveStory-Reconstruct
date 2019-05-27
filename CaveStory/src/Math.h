#pragma once
#include "Vector2d.h"
#include "units.h"

template <typename T>
inline T lerp(const T& src, const T& dst, float t) {
	return src * (1 - t) + dst * t;
}