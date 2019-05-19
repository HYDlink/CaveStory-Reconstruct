#include "PlayerPhysics.h"

void PlayerPhysics::handleInput(const Uint8* inputs) {
	if (inputs[SDL_SCANCODE_A])
		movingLeft();
	else if (inputs[SDL_SCANCODE_D])
		movingRight();
	else//TODO 在空中保持x速度，现在这样在空中回到地面速度还会保持不变
		stopMoving();

	if (inputs[SDL_SCANCODE_K])
		startJump();
	else
		stopJump();
}

void PlayerPhysics::update(units::MS deltaTime) {
	updateX(deltaTime);
	updateY(deltaTime);
#ifdef DEBUG_POS
	if (lastXPos_ != xPos_ || lastYPos_ != yPos_) {
		lastXPos_ = xPos_, lastYPos_ = yPos_;
		cout << xPos_ << " " << yPos_ << endl;
	}
#endif
}

//
void PlayerPhysics::updateX(units::MS deltaTime) {
	units::Game deltaX= round(velocityX_ * deltaTime);
	velocityX_ += accelerationX_ * deltaTime;
	if (accelerationX_ < 0)
		velocityX_ = std::max(velocityX_, -maxVelocityX);
	else if (accelerationX_ > 0)
		velocityX_ = std::min(velocityX_, maxVelocityX);
	else if (onGround_)
		velocityX_ *= slowdown;
	collision_->xCollide(deltaX);
}

void PlayerPhysics::updateY(units::MS deltaTime) {
	const units::Pixel lowest = 288;
	if (!jumping_ && velocityY_ < 0)//跳跃中途放开跳跃键，加大向下的加速度，来控制跳跃高度
		velocityY_ += stopJumpAccelerate * deltaTime;
	else
		velocityY_ += gravity * deltaTime;
	if (velocityY_ > 0)
		jumping_ = false;

	velocityY_ = std::max(velocityY_, -maxVelocityY);
	units::Game deltaY = velocityY_ * deltaTime;
	collision_->yCollide(deltaY);
}

void PlayerPhysics::movingLeft() {
	accelerationX_ = -accelerate;
	stopedmoving_ = false;
}

void PlayerPhysics::movingRight() {
	accelerationX_ = accelerate;
	stopedmoving_ = false;
}

void PlayerPhysics::stopMoving() {
	accelerationX_ = 0;
	stopedmoving_ = true;
}

void PlayerPhysics::startJump() {
	if (onGround_) {
		velocityY_ = -jumpSpeed;
		jumping_ = true;
		onGround_ = false;
	}
}

void PlayerPhysics::stopJump() {
	jumping_ = false;
}
