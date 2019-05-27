#include "Camera.h"
#include "Graphics.h"
#include "Math.h"

namespace {
	constexpr const units::MS moveTime = 300;
}

Camera::Camera(): rect_(0, 0, screenWidth, screenHeight)  {}

Camera::Camera(Position2D pos) : rect_(pos.x, pos.y, screenWidth, screenHeight) {}

Camera::Camera(const Rectangle& rect) : rect_(rect) {}

void Camera::restrict(Rectangle t) { restrict_ = t; }

//没有使用引用追踪物体，这也意味着这个要在update里面写上
void Camera::follow(Position2D pos) {
	targetPos_ = pos;
}


void Camera::update(units::MS deltaTime) {
	curPos_ = targetPos_; //lerp(curPos_, targetPos_, deltaTime / moveTime);
	auto tmpRect = rect_;
	tmpRect.setLeft(curPos_.x - rect_.width() / 2);
	tmpRect.setTop(curPos_.y - rect_.height() / 2);
	//与限制窗口的碰撞检测
	auto collideSide = tmpRect.totalIn(restrict_);
	if (collideSide & sides::LEFT_SIDE)
		tmpRect.setLeft(restrict_.left());
	else if (collideSide & sides::RIGHT_SIDE)
		tmpRect.setRight(restrict_.right());
	if (collideSide & sides::TOP_SIDE)
		tmpRect.setTop(restrict_.top());
	else if (collideSide & sides::BOTTOM_SIDE)
		tmpRect.setBottom(restrict_.bottom());
	rect_ = tmpRect;
}

bool Camera::isInCamera(Rectangle rect) const {
	return rect_.collidesWith(rect);
}

Position2D Camera::currentPos() const { return rect_.pos(); }

Rectangle Camera::currentRect() const { return rect_; }
