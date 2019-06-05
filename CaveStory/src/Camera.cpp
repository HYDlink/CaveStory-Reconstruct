#include "Camera.h"
#include "Graphics/Graphics.h"
#include "Math.h"

namespace {
	constexpr const units::MS moveTime = 300;
}

Camera::Camera(): viewPort_(0, 0, screenWidth, screenHeight)  {}

Camera::Camera(Position2D pos) : 
	curPos_(pos), viewPort_(pos.x, pos.y, screenWidth, screenHeight) {
	Rectangle::setRectByCenter(viewPort_, curPos_);
}

Camera::Camera(const Rectangle& rect) : viewPort_(rect) {}

void Camera::setRestrict(Rectangle t) { restrict_ = t; }


//没有使用引用追踪物体，这也意味着这个要在update里面写上
void Camera::follow(Position2D pos) {
	targetPos_ = pos;
}

void Camera::update(units::MS deltaTime) {
	curPos_ = targetPos_; //lerp(curPos_, targetPos_, deltaTime / moveTime);
	auto tmpView = viewPort_;
	Rectangle::setRectByCenter(tmpView, curPos_);
	restrict(tmpView);
}

//与限制窗口的碰撞检测
void Camera::restrict(Rectangle tmpView)
{
	auto collideSide = tmpView.totalIn(restrict_);
	if (collideSide & sides::LEFT_SIDE)
		tmpView.setLeft(restrict_.left());
	else if (collideSide & sides::RIGHT_SIDE)
		tmpView.setRight(restrict_.right());
	if (collideSide & sides::TOP_SIDE)
		tmpView.setTop(restrict_.top());
	else if (collideSide & sides::BOTTOM_SIDE)
		tmpView.setBottom(restrict_.bottom());
	viewPort_ = tmpView;
}

bool Camera::isInCamera(Rectangle rect) const {
	return viewPort_.collidesWith(rect);
}

Position2D Camera::currentPos() const { return viewPort_.pos(); }

Rectangle Camera::currentRect() const { return viewPort_; }
