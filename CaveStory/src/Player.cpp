#include "Player.h"
#define DEBUG_STATE

using namespace std;

struct CollisionInfo {
	units::Game row, col;
	bool collided;
};

CollisionInfo getCollisionInfo(const Map& map, const Rectangle& rectangle) {
	//���Ǻܶ�,��������������ײrectangle��̫���ܿ�Խ������ͼ������
	vector<CollisionTile> collisions = map.getCollidingTiles(rectangle);
	CollisionInfo info{ 0, 0, false };
	for (const CollisionTile& collision : collisions) {
		if (collision.type == Map::WALL) {
			info.collided = true;
			info.row = collision.row;
			info.col = collision.col;
			break;
		}
	}
	return info;
}

//����������������ʲô����, û����
Player::Player(Graphics& graphics, std::shared_ptr<Map> map, const string& filename, units::Game xPos, units::Game yPos)
	: clipRects_(CharTypeSprites / 2, vector<SDL_Rect>(MotionSprites * 2)), map_(map), 
	xPos_(xPos), yPos_(yPos), velocityX_(0), velocityY_(0), accelerationX_(0),
	lastXPos_(xPos), lastYPos_(yPos), 
    onGround_(false), jumping_(false){
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
//������! �������ܻ��animator��
void Player::setAimator() {
	animator_->setStates(getState(CharState{ WALKING, FACING_LEFT, FORWARD }), 0, 2);
	animator_->setStates(getState(CharState{ STANDING, FACING_LEFT, FORWARD }), 0, 0);
	animator_->setStates(getState(CharState{ WALKING, FACING_LEFT, LOOKUP }), 3, 5);
	animator_->setStates(getState(CharState{ STANDING, FACING_LEFT, LOOKUP }), 3, 3);
	animator_->setStates(getState(CharState{ JUMPING, FACING_LEFT, FORWARD }), 2, 2);
	animator_->setStates(getState(CharState{ FALLING, FACING_LEFT, FORWARD }), 1, 1);
	animator_->setStates(getState(CharState{ JUMPING, FACING_LEFT, LOOKUP }), 4, 4);
	animator_->setStates(getState(CharState{ FALLING, FACING_LEFT, LOOKUP }), 4, 4);
	//TODO ��ɫ�ڽӴ��������һ��,��һ�����嶯��,�м仹��һ������֡,Ҳ����λ��5
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
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W])
		lookUp();
	else if (state[SDL_SCANCODE_S]) {
		interactOrLookDown();
	}
	else
		lookForward();

	if (state[SDL_SCANCODE_A])
		movingLeft();
	else if (state[SDL_SCANCODE_D])
		movingRight();
	else//TODO �ڿ��б���x�ٶȣ����������ڿ��лص������ٶȻ��ᱣ�ֲ���
		stopMoving();
	
	if (state[SDL_SCANCODE_K])
		startJump();
	else
		stopJump();

}

void Player::update(units::MS deltaTime) {
	updateX(deltaTime);
	updateY(deltaTime);
	updateState();
	updateDebug();
	animator_->triggerState(getState(state_));
}
void Player::updateX(units::MS deltaTime) {
	animation_->update();
	units::Game deltaX = round(velocityX_ * deltaTime);
	velocityX_ += accelerationX_ * deltaTime;
	if (accelerationX_ < 0)
		velocityX_ = std::max(velocityX_, -maxVelocityX);
	else if (accelerationX_ > 0)
		velocityX_ = std::min(velocityX_, maxVelocityX);
	else if (onGround_)
		velocityX_ *= slowdown;
	if (deltaX > 0) {
		CollisionInfo info = getCollisionInfo(*map_, rightCollision(deltaX));
		if (info.collided) {
			xPos_ = info.row * units::TileSize - CollisionX.right();
			velocityX_ = 0;
		}
		else {
			xPos_ += deltaX;
		}
	}
	else {
		CollisionInfo info = getCollisionInfo(*map_, leftCollision(-deltaX));//������Ҫ����
		if (info.collided) {
			xPos_ = (info.row + 1) * units::TileSize - CollisionX.left();
			velocityX_ = 0;
		}
		else {
			xPos_ += deltaX;
		}
	}
}

void Player::updateY(units::MS deltaTime) {

	const units::Pixel lowest = 288;//��ʱ��͵�
	if (!jumping_ && velocityY_ < 0)//��Ծ��;�ſ���Ծ�����Ӵ����µļ��ٶȣ���������Ծ�߶�
		velocityY_ += stopJumpAccelerate * deltaTime;
	else
		velocityY_ += gravity * deltaTime;
	if (velocityY_ > 0)
		jumping_ = false;

	velocityY_ = std::max(velocityY_, -maxVelocityY);
	units::Game deltaY = velocityY_ * deltaTime;

	if (deltaY > 0) {
		CollisionInfo info = getCollisionInfo(*map_, bottomCollision(deltaY));
		if (info.collided) {
			yPos_ = info.col* units::TileSize - CollisionY.bottom();
			onGround_ = true;
			velocityY_ = 0;
		}
		else {
			yPos_ += deltaY;
			onGround_ = false;
		}
	}
	else {
		CollisionInfo info = getCollisionInfo(*map_, topCollision(-deltaY));//������Ҫ����
		if (info.collided) {
			yPos_ = (info.col + 1) * units::TileSize - CollisionY.top();
			velocityY_ = 0;
			jumping_ = false;
		}
		else {
			yPos_ += deltaY;
		}
	}
}

//�ȽϾ�������ܲ������˶���ʱ����
void Player::updateState() {
	if (onGround_) { //����Ӱ�����ڵ����interact
		if (state_.motionType == INTERACTING);
		else if (stopedmoving_)
			state_.motionType = STANDING;
		else
			state_.motionType = WALKING;
	}
	if (!onGround_) {
		if (velocityY_ < error) {
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
	SDL_Rect pos{ units::gameToPixel(xPos_), units::gameToPixel(yPos_), 0, 0 };
	animation_->draw(graphics, &pos);
}

void Player::movingLeft() {
	accelerationX_ = -accelerate;
	stopedmoving_ = false;
	state_.horizontalFacing = FACING_LEFT;
}

void Player::movingRight() {
	accelerationX_ = accelerate;
	stopedmoving_ = false;
	state_.horizontalFacing = FACING_RIGHT;
}

void Player::stopMoving() {
	accelerationX_ = 0;
	stopedmoving_ = true;
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

void Player::lookForward() {
	if (state_.motionType == INTERACTING)
		state_.motionType = STANDING;
	state_.verticalFacing = FORWARD;
}

void Player::lookUp() {
	state_.verticalFacing = LOOKUP;
}

void Player::interactOrLookDown() {
	//�ڹ۲�/���������н�ֹ����ƶ�
	//���ûʵ�ְ�, �Ȳ�����
	if (onGround_) {
		state_.motionType = INTERACTING;
		accelerationX_ = 0;
		velocityX_ = 0;
	}
	else
		state_.verticalFacing = LOOKDOWN;
}

Rectangle Player::leftCollision(units::Game delta) {
	return Rectangle(
		xPos_ + CollisionX.left() - delta,
		yPos_ + CollisionX.top(),
		CollisionX.width() / 2 - delta,
		CollisionX.height()
	);
}

Rectangle Player::rightCollision(units::Game delta) {
	return Rectangle(
		xPos_ + CollisionX.width() / 2 + CollisionX.left() + delta,
		yPos_ + CollisionX.top(),
		CollisionX.width() / 2 + delta,
		CollisionX.height()
	);
}

Rectangle Player::topCollision(units::Game delta) {
	//delta�������Ϸ���ľ���ֵ?
	assert(delta >= 0);
	return Rectangle(
		xPos_ + CollisionY.left(),
		yPos_ + CollisionY.top() - delta,
		CollisionY.width(),
		CollisionY.height() / 2 + delta
	);
}

Rectangle Player::bottomCollision(units::Game delta) {
	return Rectangle(
		xPos_ + CollisionY.left(),
		yPos_ + CollisionY.height()/2 + CollisionY.top() + delta,
		CollisionY.width(),
		CollisionY.height() / 2 + delta
	);
}
