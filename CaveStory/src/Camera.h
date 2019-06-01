#pragma once

#include "Utils/units.h"
#include "Rectangle.h"
#include "GameObject.h"
class Camera {
public:
	Camera();
	// 设置Camera中心位置
	Camera(Position2D pos);
	// 设置Camera视角
	Camera(const Rectangle& rect);
	virtual ~Camera() {}
	// 保持Camera视角在限定视角以内
	void setRestrict(Rectangle t);
	void follow(Position2D pos);
	virtual void update(units::MS deltaTime);
	void restrict(Rectangle tmpRect);// restrict是c99关键字
	bool isInCamera(Rectangle) const;
	Position2D currentPos() const;
	Rectangle currentRect() const;
protected:
	Rectangle viewPort_;
	Rectangle restrict_;
	Position2D curPos_,targetPos_;// 都表示相机中心位置
};