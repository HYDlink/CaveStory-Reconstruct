#include "Player.h"
#include "Components/PlayerPhysics.h"
#include "Components/CollisionComponent.h"
#include "Graphics/Animation.h"
#include "Animator.h"

using namespace std;

namespace {
	const units::MS InvisibleTime = 1500;
	const units::MS InvisibleFlashTime = 50;
	const units::HP InitialHP = 20;
	const Rectangle CollisionX{ 6, 10, 20, 12 };
	const Rectangle CollisionY{ 10, 2, 12, 30 };
}

Player::Player(Graphics& graphics, std::shared_ptr<ForeGround> map, const string& filename, 
	units::Game xPos, units::Game yPos,	NumberSprite& numberSprite)
	: GameObject(LAYER::PLAYER), clipRects_(CharTypeSprites, vector<SDL_Rect>(MotionSprites)),
	  physics_(new PlayerPhysics(this, xPos, yPos)), 
	collision_(new CollisionComponent(physics_, CollisionX, CollisionY, map)),
	  invisibleTimer_(InvisibleTime), healthBar_(graphics, "res/TextBox.bmp", InitialHP, numberSprite),
	  numberSprite_(numberSprite), damageText_(numberSprite_),
	  weapon(graphics, WeaponType::POLARSTAR, *this)
    {
	physics_->setCollision(collision_);
	setClipRect();
	animation_ = make_shared<Animation>(graphics, filename, clipRects_[0]);
	animator_ = make_shared<Animator>(animation_);
	setAimator();
	children_.emplace_back(make_shared<HelathBar>(healthBar_));
	children_.emplace_back(make_shared<Weapon>(weapon));
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
//不修了! 反正可能会改animator类
void Player::setAimator() {
	animator_->setStates(getState(CharState{ WALKING, FORWARD }), 0, 2);
	animator_->setStates(getState(CharState{ STANDING, FORWARD }), 0, 0);
	animator_->setStates(getState(CharState{ WALKING, LOOKUP }), 3, 5);
	animator_->setStates(getState(CharState{ STANDING, LOOKUP }), 3, 3);
	animator_->setStates(getState(CharState{ JUMPING, FORWARD }), 2, 2);
	animator_->setStates(getState(CharState{ FALLING, FORWARD }), 1, 1);
	animator_->setStates(getState(CharState{ JUMPING, LOOKUP }), 4, 4);
	animator_->setStates(getState(CharState{ FALLING, LOOKUP }), 4, 4);
	//TODO 角色在接触地面的那一刻, 有一个缓冲动画,中间还有一个动画帧,也就是位置5
	animator_->setStates(getState(CharState{ JUMPING, LOOKDOWN }), 6, 6);
	animator_->setStates(getState(CharState{ FALLING, LOOKDOWN }), 6, 6);
	animator_->setStates(getState(CharState{ INTERACTING, FORWARD }), 7, 7);
	//animation_->start_Animation(0, 2, 4, true);
}

void Player::setNumberSprite(NumberSprite& numberSprite) {
	numberSprite_ = numberSprite;
	healthBar_.setNumberSprite(numberSprite);
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
		state_.horizontalFacing = FACING_LEFT;
	else if (inputs[SDL_SCANCODE_D])
		state_.horizontalFacing = FACING_RIGHT;

	physics_->handleInput(inputs);

	if (inputs[SDL_SCANCODE_J])
		weapon.launch();
}

void Player::update(units::MS deltaTime) {
	//无敌时间处理
	if (invisible_) {
		invisible_ = invisibleTimer_.isActive();
	}
	physics_->update(deltaTime);
	updateState();
	updateDebug();
	animator_->triggerState(getState(state_));
	animation_->flip(state_.horizontalFacing ? SDL_FLIP_HORIZONTAL: SDL_FLIP_NONE);
	animation_->update();
	healthBar_.update(deltaTime);
	damageText_.setPos(Position2D(pos().x + units::HalfTile, pos().y));
	damageText_.update(deltaTime);
}

//比较纠结这个能不能在运动的时候修
void Player::updateState() {
	if (physics_->onGround_) { //这里影响了在地面的interact
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

void Player::draw(Graphics& graphics) const {
	//角色受伤闪烁，也可以设置成变透明或者变亮
	//由于healtBar必须在这里绘制，所以invisible时healthBar也不会绘制，不必为healthBar多设置一个闪烁方法
	if (invisible_ && (invisibleTimer_.currentTime() / InvisibleFlashTime) % 3 == 0)
		return;
	SDL_Rect pos{ units::gameToPixel(physics_->xPos_), units::gameToPixel(physics_->yPos_), 0, 0 };
	animation_->draw(graphics, &pos);
	//healthBar_.draw(graphics);
	damageText_.draw(graphics);
}

const std::shared_ptr<Animation> Player::getAnimation() const 
{ return animation_; }

Position2D Player::pos() const
{ return Position2D{ physics_->xPos_, physics_->yPos_ }; }

Position2D Player::centerPos() const {
	return pos() + units::HalfTile;
}

units::Velocity Player::velX() const {
	return physics_->velocityX_;
}

units::Velocity Player::velY() const {
	return physics_->velocityY_;
}

CharState Player::state() const {
	return state_;
}

std::vector<Rectangle> Player::collider() const {
	return collision_->collisions();
}

//角色受伤：小跳一次，短暂无敌
void Player::takeDamage(units::HP damage) {
	if (invisible_)//无敌时间
		return;
	hp_ -= damage;
	healthBar_.takeDamage(damage);
	damageText_.active(-damage);
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
	//TODO 开始交互的动画的那一段时间角色不能移动，并且头上浮出问号或者开始交互事件，
	//然后任何按钮都可以中断这个动作
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
