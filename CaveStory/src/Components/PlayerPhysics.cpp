#include "PlayerPhysics.h"

using namespace std;
namespace {
	const units::Velocity maxVelocityX = 0.15859375f;
	const units::Velocity maxVelocityY = 0.30f;
}


PlayerPhysics::PlayerPhysics(Player* player, units::Game xPos, units::Game yPos, 
	CollisionComponent* collision) :
	player_(player), PhysicsComponent(xPos, yPos, maxVelocityX, maxVelocityY),
	onGround_(false), jumping_(false),
	collision_(collision) {
}

void PlayerPhysics::handleInput(const Uint8* inputs) {
	if (inputs[SDL_SCANCODE_A])
		movingLeft();
	else if (inputs[SDL_SCANCODE_D])
		movingRight();
	else
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
	units::Game deltaX = round(velocityX_ * deltaTime);
	velocityX_ += accelerationX_ * deltaTime;
	if (accelerationX_ < 0)
		velocityX_ = std::max(velocityX_, -maxVelocityX_);
	else if (accelerationX_ > 0)
		velocityX_ = std::min(velocityX_, maxVelocityX_);
	else if (onGround_)
		velocityX_ *= slowdown;
	collision_->xCollide(deltaX);
}

void PlayerPhysics::updateY(units::MS deltaTime) {
	const units::Pixel lowest = 288;
	if (!jumping_ && velocityY_ < 0)//跳跃中途放开跳跃键，加大向下的加速度，来控制跳跃高度
		accelerationY_ = stopJumpAccelerate;
	else
		accelerationY_ = gravity;
	velocityY_ += accelerationY_ * deltaTime;

	if (accelerationY_ < 0)
		velocityY_ = std::max(velocityY_, -maxVelocityY_);
	else if (accelerationY_ > 0)
		velocityY_ = std::min(velocityY_, maxVelocityY_);

	if (velocityY_ > 0)
		jumping_ = false;
	units::Game deltaY = velocityY_ * deltaTime;
	//C++17写法，yCollide毕竟有副作用，不知道这样写好不好
	const auto collided = collision_->yCollide(deltaY);
	if (deltaY > 0)
		onGround_ = collided;
	else if (collided)
		jumping_ = false;
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