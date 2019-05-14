#include "Player.h"

using namespace std;


Player::Player(Graphics& graphics, const string& filename, Uint16 xPos, Uint16 yPos)
	: clipRects_(CharTypeSprites / 2, vector<SDL_Rect>(MotionSprites * 2)),
	xPos_(xPos), yPos_(yPos), velocityX_(0), velocityY_(0), accelerationX_(0),
    onGround_(false), jumping_(false){
	setClipRect();
	animation_ = make_shared<Animation>(graphics, filename, clipRects_[0]);
	animator_ = make_shared<Animator>(animation_);
	setAimator();
}


Player::~Player() {
}

void Player::setClipRect() {
	Uint8 width = 32;
	for(int i = 0; i < CharTypeSprites; ++i)
		for (int j = 0; j < MotionSprites; ++j) {
			clipRects_[i / 2][(i % 2) * MotionSprites + j] 
				= SDL_Rect{ j * width, i * width, width, width };
		}
}

void Player::setAimator() {
	animator_->setStates(getState(WALKING, FACING_LEFT), 0, 2);
	animator_->setStates(getState(STANDING, FACING_LEFT), 0, 0);
	animator_->setStates(getState(WALKING, FACING_RIGHT), MotionSprites, MotionSprites + 2);
	animator_->setStates(getState(STANDING, FACING_RIGHT), MotionSprites, MotionSprites);
	//animation_->start_Animation(0, 2, 4, true);
}

//https://wiki.libsdl.org/SDL_GetKeyboardState
void Player::handleEvent(SDL_Event& e) {
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A])
		movingLeft();
	else if (state[SDL_SCANCODE_D])
		movingRight();
	else if(onGround_)//TODO 在空中保持x速度，现在这样在空中回到地面速度还会保持不变
		stopMoving();
	
	if (state[SDL_SCANCODE_K])
		startJump();
	else
		stopJump();
}
void Player::update() {
	updateX();
	updateY();
}
void Player::updateX() {
	animation_->update();
	xPos_ += round(velocityX_);
	velocityX_ += accelerationX_;
	if (accelerationX_ < 0)
		velocityX_ = std::max(velocityX_, -maxVelocityX);
	else if (accelerationX_ > 0)
		velocityX_ = std::min(velocityX_, maxVelocityX);
	else if (velocityX_ >= 0.5f && onGround_)
		velocityX_ *= slowdown;
	else
		velocityX_ = 0;
	//cout << accelerationX_ << " " << velocityX_ << " " << xPos_ << endl;
}

void Player::updateY() {
	const int lowest = 288;
	if (!jumping_ && velocityY_ < 0)//跳跃中途放开跳跃键，加大向下的加速度，来控制跳跃高度
		velocityY_ += stopJumpAccelerate;
	else
		velocityY_ += gravity;
	velocityY_ = std::max(velocityY_, -maxVelocityY);
	yPos_ += velocityY_;
	if (yPos_ > lowest) {//lowest是暂时的最低点，以后要用碰撞体检测替代
		onGround_ = true;
		yPos_ = lowest;
		velocityY_ = 0;
	}
}

void Player::draw(Graphics& graphics) {
	SDL_Rect pos{ xPos_, yPos_, 0, 0 };
	animation_->draw(graphics, &pos);
}

void Player::movingLeft() {
	accelerationX_ = -accelerate;
	currentFacing_ = FACING_LEFT;
	animator_->triggerState(getState(WALKING, FACING_LEFT));
}

void Player::movingRight() {
	accelerationX_ = accelerate;
	currentFacing_ = FACING_RIGHT;
	animator_->triggerState(getState(WALKING, FACING_RIGHT));
}

void Player::stopMoving() {
	accelerationX_ = 0;
	animator_->triggerState(getState(STANDING, currentFacing_));
}

void Player::startJump() {
	if (onGround_) {
		velocityY_ = -jumpSpeed;
		jumping_ = true;
		onGround_ = false;
	}
}

void Player::stopJump() {
	jumping_ = false;
}

void Player::lookUp() {
}
