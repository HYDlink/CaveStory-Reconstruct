#include "Player.h"
#include "Components/PlayerPhysics.h"
#include "Components/PlayerCollision.h"
#include "State.h"
#define DEBUG_STATE

using namespace std;


Player::Player(Graphics& graphics, std::shared_ptr<Map> map, const string& filename,
	units::Game xPos, units::Game yPos)
	: clipRects_(CharTypeSprites / 2, vector<SDL_Rect>(MotionSprites * 2)), map_(map),
	  physics_(new PlayerPhysics(this, xPos, yPos)), motionState_(new StandState()),
	  collision_(new PlayerCollision(this, physics_, map))
    {
	physics_->setCollision(collision_);
	setClipRect();
	animation_ = make_shared<Animation>(graphics, filename, clipRects_[0]);
	animator_ = make_shared<Animator>(animation_);
	setAimator();
}


Player::~Player() {
}

void Player::setClipRect() {
	for(units::Frame i = 0; i < CharTypeSprites; ++i)
		for (units::Frame j = 0; j < MotionSprites; ++j) {
			clipRects_[i / 2][(i % 2) * MotionSprites + j] 
				= SDL_Rect{ j * units::TileSize, i * units::TileSize, units::TileSize, units::TileSize };
		}
}

//shit mountain?
//不修了! 反正可能会改animator类
void Player::setAimator() {
	animator_->setStates(getState(CharState{ WALKING, FACING_LEFT, FORWARD }), 0, 2);
	animator_->setStates(getState(CharState{ STANDING, FACING_LEFT, FORWARD }), 0, 0);
	animator_->setStates(getState(CharState{ WALKING, FACING_LEFT, LOOKUP }), 3, 5);
	animator_->setStates(getState(CharState{ STANDING, FACING_LEFT, LOOKUP }), 3, 3);
	animator_->setStates(getState(CharState{ JUMPING, FACING_LEFT, FORWARD }), 2, 2);
	animator_->setStates(getState(CharState{ FALLING, FACING_LEFT, FORWARD }), 1, 1);
	animator_->setStates(getState(CharState{ JUMPING, FACING_LEFT, LOOKUP }), 4, 4);
	animator_->setStates(getState(CharState{ FALLING, FACING_LEFT, LOOKUP }), 4, 4);
	//TODO 角色在接触地面的那一刻, 有一个缓冲动画,中间还有一个动画帧,也就是位置5
	animator_->setStates(getState(CharState{ JUMPING, FACING_LEFT, LOOKDOWN }), 6, 6);
	animator_->setStates(getState(CharState{ FALLING, FACING_LEFT, LOOKDOWN }), 6, 6);
	animator_->setStates(getState(CharState{ INTERACTING, FACING_LEFT, FORWARD }), 7, 7);
	animator_->setStates(getState(CharState{ WALKING, FACING_RIGHT, FORWARD }), MotionSprites, MotionSprites + 2);
	animator_->setStates(getState(CharState{ STANDING, FACING_RIGHT, FORWARD }), MotionSprites, MotionSprites);
	animator_->setStates(getState(CharState{ WALKING, FACING_RIGHT, LOOKUP }), MotionSprites + 3, MotionSprites + 5);
	animator_->setStates(getState(CharState{ STANDING, FACING_RIGHT, LOOKUP }), MotionSprites + 3, MotionSprites + 3);
	animator_->setStates(getState(CharState{ JUMPING, FACING_RIGHT, FORWARD }), MotionSprites + 2, MotionSprites + 2);
	animator_->setStates(getState(CharState{ FALLING, FACING_RIGHT, FORWARD }), MotionSprites + 1, MotionSprites + 1);
	animator_->setStates(getState(CharState{ JUMPING, FACING_RIGHT, LOOKUP }), MotionSprites + 4, MotionSprites + 4);
	animator_->setStates(getState(CharState{ FALLING, FACING_RIGHT, LOOKUP }), MotionSprites + 4, MotionSprites + 4);
	animator_->setStates(getState(CharState{ JUMPING, FACING_RIGHT, LOOKDOWN }), MotionSprites + 6, MotionSprites + 6);
	animator_->setStates(getState(CharState{ FALLING, FACING_RIGHT, LOOKDOWN }), MotionSprites + 6, MotionSprites + 6);
	animator_->setStates(getState(CharState{ INTERACTING, FACING_RIGHT, FORWARD }), MotionSprites + 7, MotionSprites + 7);
	//animation_->start_Animation(0, 2, 4, true);
}

//https://wiki.libsdl.org/SDL_GetKeyboardState
void Player::handleEvent(SDL_Event& e) {
	const Uint8* inputs = SDL_GetKeyboardState(NULL);
	if (inputs[SDL_SCANCODE_W])
		lookUp();
	else if (inputs[SDL_SCANCODE_S]) {
		interactOrLookDown();
	}
	else
		lookForward();

	physics_->handleInput(inputs);
}

void Player::update(units::MS deltaTime) {
	physics_->update(deltaTime);
	motionState_->update(*this);
	state_.motionType = static_cast<MotionType>(motionState_->type);

	//updateState();
	updateDebug();
	animator_->triggerState(getState(state_));
	animation_->update();
}

//比较纠结这个能不能在运动的时候修
void Player::updateState() {
	if (physics_->onGround_) {
		if (physics_->stopedmoving_) {
			if (state_.motionType != INTERACTING)
				state_.motionType = STANDING;
		}
		else
			state_.motionType = WALKING;
	}
	if (!physics_->onGround_) {
		if (physics_->velocityY_ < physics_->error) {
			state_.motionType = JUMPING;
		}
		else {
			state_.motionType = FALLING;
		}
	}
}

void Player::updateDebug() {
#ifdef DEBUG_POS
	if (lastXPos_ != xPos_ || lastYPos_ != yPos_) {
		lastXPos_ = xPos_, lastYPos_ = yPos_;
		cout << xPos_ << " " << yPos_ << endl;
	}
#endif
#ifdef DEBUG_STATE
	if (getState(lastState_) != getState(state_)) {
		lastState_ = state_;
		cout << getState(state_) << endl;
	}
#endif
}

void Player::draw(Graphics& graphics) {
	SDL_Rect pos{ units::gameToPixel(physics_->xPos_), units::gameToPixel(physics_->yPos_), 0, 0 };
	animation_->draw(graphics, &pos);
}

void Player::lookForward() {
	if (state_.motionType == INTERACTING)
		state_.motionType = STANDING;
	state_.verticalFacing = FORWARD;
}

void Player::lookUp() {
	state_.verticalFacing = LOOKUP;
}

void Player::interactOrLookDown() {
	if (physics_->onGround_) {
		if (physics_->velocityX_ == 0)
			state_.motionType = INTERACTING;
	}
	else
		state_.verticalFacing = LOOKDOWN;
}

inline bool Player::onGround() const { return physics_->onGround_; }

inline bool Player::jumping() const { return physics_->jumping_; }

void Player::changeState(State* state) {
	motionState_ = state;
}
