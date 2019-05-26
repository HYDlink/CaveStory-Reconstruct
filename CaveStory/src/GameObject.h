#pragma once
#include "units.h"
class Graphics;
class GameObject {
public:
	GameObject() {}
	~GameObject() = default;
	virtual void update(units::MS deltaTime) = 0;
	virtual void draw(Graphics& graphics) const = 0;
};