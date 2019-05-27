#pragma once
#include "Vector2d.h"
#include "units.h"

template <typename T>
inline T lerp(const T& src, const T& dst, float t) {
	return src * (1 - t) + dst * t;
}

template <typename T>
inline T clamp(const T& cur, const T& min, const T& max) {
	if (cur < min)
		return min;
	else if (cur > max)
		return max;
	else
		return cur;
}

inline units::Game 
SmoothDamp(units::Game current, units::Game target, units::Velocity& currentVelocity,
	units::MS smoothTime, units::MS deltaTime, float maxSpeed) {
	smoothTime = std::max(static_cast<units::MS>(10), smoothTime);
	float omega = 2.0f / smoothTime;
	float x = omega * deltaTime;
	float exp = 1.0f / (1.0f + x + 0.48 * x * x + 0.235 * x * x * x);
	float deltaX = target - current;
	float maxDelta = maxSpeed * smoothTime;

	// ensure we do not exceed our max speed
	deltaX = clamp(deltaX, -maxDelta, maxDelta);
	float temp = (currentVelocity + omega * deltaX) * deltaTime;
	float result = current - deltaX + (deltaX + temp) * exp;
	currentVelocity = (currentVelocity - omega * temp) * exp;

	// ensure that we do not overshoot our target
	if (target - current > 0.0f == result > target) {
		result = target;
		currentVelocity = 0.0f;
	}
	return result;
}

inline
float SmoothDamp(float current, float target, float& currentVelocity, 
	float smoothTime,
	units::MS deltaTime, float maxSpeed = FLT_MAX) {
	smoothTime = std::max(0.0001f, smoothTime);
	float omega = 2.0f / smoothTime;
	float x = omega * deltaTime;
	float exp = 1.0f / (1.0f + x + 0.48 * x * x + 0.235 * x * x * x);
	float deltaX = target - current;
	float maxDelta = maxSpeed * smoothTime;

	// ensure we do not exceed our max speed
	deltaX = clamp(deltaX, -maxDelta, maxDelta);
	float temp = (currentVelocity + omega * deltaX) * deltaTime;
	float result = current - deltaX + (deltaX + temp) * exp;
	currentVelocity = (currentVelocity - omega * temp) * exp;

	// ensure that we do not overshoot our target
	if (target - current > 0.0f == result > target) {
		result = target;
		currentVelocity = 0.0f;
	}
	return result;
}