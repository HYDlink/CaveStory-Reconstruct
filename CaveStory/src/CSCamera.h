#pragma once
#include "Camera.h"
#include <memory>

class PhysicsComponent;
class Player;
class CSCamera :public Camera {
public:
	CSCamera();
	CSCamera(std::shared_ptr<Player> player);
	void setPlayer(std::shared_ptr<Player> player);
	virtual void update(units::MS deltaTime) override;
protected:
	std::shared_ptr<Player> player_;
	//units::Game deadZoneX, deadZoneY;
	units::Velocity velX;
	PhysicsComponent* physics;
};