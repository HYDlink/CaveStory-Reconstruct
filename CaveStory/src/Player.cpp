#include "Player.h"
#include "Components/PlayerPhysics.h"
#include "Components/PlayerCollision.h"

using namespace std;

namespace {
	const units::MS InvisibleTime = 1500;
	const units::MS InvisibleFlashTime = 50;
}

Player::Player(Graphics& graphics, std::shared_ptr<Map> map, const string& filename, 
	units::Game xPos, units::Game yPos)
	: clipRects_(CharTypeSprites, vector<SDL_Rect>(MotionSprites)),
	  physics_(new PlayerPhysics(this, xPos, yPos)), collision_(new PlayerCollision(this, physics_, map)),
	  invisibleTimer_(InvisibleTime), healthBar_(graphics, "res/TextBox.bmp", 3)
    {
	physics_->setCollision(collision_);
	setClipRect();
	animation_ = make_shared<Animation>(graphics, filename, clipRects_[0]);
	animator_ = make_shared<Animator>(animation_);
	setAimator();
}


Player::~Player() {}

void Player::setClipRect() {
	for(units::Frame i = 0; i < CharTypeSprites; ++i)
		for (units::Frame j = 0; j < MotionSprites; ++j) {
			clipRects_[i][j] 
				= SDL_Rect{ j * units::TileSize, i * units::TileSize, units::TileSize, units::TileSize };
		}
}

//shit mountain?
//������! �������ܻ��animator��
void Player::setAimator() {
	animator_->setStates(getState(CharState{ WALKING, FORWARD }), 0, 2);
	animator_->setStates(getState(CharState{ STANDING, FORWARD }), 0, 0);
	animator_->setStates(getState(CharState{ WALKING, LOOKUP }), 3, 5);
	animator_->setStates(getState(CharState{ STANDING, LOOKUP }), 3, 3);
	animator_->setStates(getState(CharState{ JUMPING, FORWARD }), 2, 2);
	animator_->setStates(getState(CharState{ FALLING, FORWARD }), 1, 1);
	animator_->setStates(getState(CharState{ JUMPING, LOOKUP }), 4, 4);
	animator_->setStates(getState(CharState{ FALLING, LOOKUP }), 4, 4);
	//TODO ��ɫ�ڽӴ��������һ��, ��һ�����嶯��,�м仹��һ������֡,Ҳ����λ��5
	animator_->setStates(getState(CharState{ JUMPING, LOOKDOWN }), 6, 6);
	animator_->setStates(getState(CharState{ FALLING, LOOKDOWN }), 6, 6);
	animator_->setStates(getState(CharState{ INTERACTING, FORWARD }), 7, 7);
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

	if (inputs[SDL_SCANCODE_A])
		horizontalFacing_ = FACING_LEFT;
	else if (inputs[SDL_SCANCODE_D])
		horizontalFacing_ = FACING_RIGHT;

	physics_->handleInput(inputs);
}

void Player::update(units::MS deltaTime) {
	//�޵�ʱ�䴦��
	if (invisible_) {
		invisible_ = invisibleTimer_.isActive();
	}
	physics_->update(deltaTime);
	updateState();
	updateDebug();
	animator_->triggerState(getState(state_));
	animation_->flip(horizontalFacing_ ? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE);
	animation_->update();
	healthBar_.update(deltaTime);
}

//�ȽϾ�������ܲ������˶���ʱ����
void Player::updateState() {
	if (physics_->onGround_) { //����Ӱ�����ڵ����interact
		if (state_.motionType == INTERACTING);
		else if (physics_->stopedmoving_)
			state_.motionType = STANDING;
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
#ifdef DEBUG_STATE
	if (getState(lastState_) != getState(state_)) {
		lastState_ = state_;
		cout << getState(state_) << endl;
	}
#endif
}

void Player::draw(Graphics& graphics) {
	//��ɫ������˸��Ҳ�������óɱ�͸�����߱���
	//����healtBar������������ƣ�����invisibleʱhealthBarҲ������ƣ�����ΪhealthBar������һ����˸����
	if (invisible_ && (invisibleTimer_.currentTime() / InvisibleFlashTime) % 3 == 0)
		return;
	SDL_Rect pos{ units::gameToPixel(physics_->xPos_), units::gameToPixel(physics_->yPos_), 0, 0 };
	animation_->draw(graphics, &pos);
	healthBar_.draw(graphics);
}

Position2D Player::pos() const { return Position2D{ physics_->xPos_, physics_->yPos_ }; }

std::vector<Rectangle> Player::collider() const {
	return collision_->collisions();
}

//��ɫ���ˣ�С��һ�Σ������޵�
void Player::takeDamage(units::HP damage) {
	if (invisible_)//�޵�ʱ��
		return;
	hp_ -= damage;
	healthBar_.takeDamage(damage);
	physics_->velocityY_ = -physics_->jumpSpeed;
	invisible_ = true;
	invisibleTimer_.reset();
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
	//TODO
	//�ڹ۲�/���������н�ֹ����ƶ�
	if (physics_->onGround_) {
		state_.motionType = INTERACTING;
		physics_->accelerationX_ = 0;
		physics_->velocityX_ = 0;
	}
	else
		state_.verticalFacing = LOOKDOWN;
}

inline bool Player::onGround() const { return physics_->onGround_; }

inline bool Player::jumping() const { return physics_->jumping_; }
