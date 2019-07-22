#pragma once
#include "../GameObject.h"
#include "units.h"
class TestObject:public GameObject {
private:
	units::MS lerpTime = 1;
	units::MS currentLerpTime;
	units::Game moveDistance = 10;
	Position2D pos_;
	const Position2D startPos = Position2D{ 20, 20 };
	const Position2D endPos = Position2D{ 120, 20 };
public:
	virtual void update(units::MS deltaTime);
	virtual void draw(Graphics& graphics) const;
};