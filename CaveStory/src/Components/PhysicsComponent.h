#pragma once
#include "../Utils/units.h"

class CollisionComponent;
class PhysicsComponent {
	friend class CollisionComponent;
public:
	PhysicsComponent(units::Game xPos = 0, units::Game yPos = 0, 
		units::Velocity maxVX = 10.0f, units::Velocity maxVY = 10.0f) :
		xPos_(xPos), yPos_(yPos), lastXPos_(xPos), lastYPos_(yPos),
		maxVelocityX_(maxVX), maxVelocityY_(maxVY){};
	virtual ~PhysicsComponent() = default;

	virtual void update(units::MS deltaTime) {
		updateX(deltaTime);
		updateY(deltaTime);
	}
	virtual void updateX(units::MS deltaTime) {
		velocityX_ += accelerationX_ * deltaTime;
		if (accelerationX_ < 0)
			velocityX_ = std::max(velocityX_, -maxVelocityX_);
		else if (accelerationX_ > 0)
			velocityX_ = std::min(velocityX_, maxVelocityX_);
		xPos_ += velocityX_ * deltaTime;
	}
	virtual void updateY(units::MS deltaTime) {
		velocityY_ += accelerationY_ * deltaTime;
		if (accelerationY_ < 0)
			velocityY_ = std::max(velocityY_, -maxVelocityY_);
		else if (accelerationY_ > 0)
			velocityY_ = std::min(velocityY_, maxVelocityY_);
		yPos_ += velocityY_ * deltaTime;
	}
	Position2D pos() const{
		return { xPos_, yPos_ };
	}
	//获得X与Y方向 速度 组成的pair
	auto getVel() const {
		return std::make_pair(velocityX_, velocityY_);
	}
	//获得X与Y方向 加速度 组成的pair
	auto getAcce() const {
		return std::make_pair(accelerationX_, accelerationY_);
	}
	void setVelX(units::Velocity vel) { velocityX_ = vel; }
	void setVelY(units::Velocity vel) { velocityY_ = vel; }
	void setAcceX(units::Acceleration acce) { accelerationX_ = acce; }
	void setVY(units::Acceleration acce) { accelerationY_ = acce; }

	const units::Velocity maxVelocityX_;
	const units::Velocity maxVelocityY_;
protected:
	units::Game xPos_ = 0, yPos_ = 0;
	units::Game lastXPos_ = 0, lastYPos_ = 0;
	units::Velocity velocityX_ = 0, velocityY_ = 0;
	units::Acceleration accelerationX_ = 0, accelerationY_ = 0;
};
