#pragma once
#include "../units.h"

class CollisionComponent;
class PhysicsComponent {
	friend class CollisionComponent;
public:
	PhysicsComponent() {};
	PhysicsComponent(units::Game xPos, units::Game yPos) :
		xPos_(xPos), yPos_(yPos), lastXPos_(xPos), lastYPos_(yPos) {};
	virtual ~PhysicsComponent() = default;

	virtual void update(units::MS deltaTime) = 0;
	virtual void updateX(units::MS deltaTime) = 0;
	virtual void updateY(units::MS deltaTime) = 0;
protected:
	units::Game xPos_ = 0, yPos_ = 0;
	units::Game lastXPos_ = 0, lastYPos_ = 0;
	units::Velocity velocityX_ = 0, velocityY_ = 0;
};
