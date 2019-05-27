#pragma once

#include "units.h"
#include "Rectangle.h"
#include "GameObject.h"
class Camera {
public:
	Camera();
	Camera(Position2D pos);
	Camera(const Rectangle& rect);
	virtual ~Camera() {}
	void restrict(Rectangle t);// restrictÊÇc99¹Ø¼ü×Ö
	void follow(Position2D pos);
	virtual void update(units::MS deltaTime);
	bool isInCamera(Rectangle) const;
	Position2D currentPos() const;
	Rectangle currentRect() const;
private:
	Rectangle rect_;
	Rectangle restrict_;
	Position2D curPos_,targetPos_;
};