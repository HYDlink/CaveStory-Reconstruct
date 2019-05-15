#ifndef PLAYER_H_
#define PLAYER_H_

#include "Animation.h"
#include "Animator.h"
#include "Rectangle.h"
#include "Map.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <tuple>

class Player {
public:
	enum MotionType : Uint8 {
		FIRST_MOTION_TYPE,
		STANDING = FIRST_MOTION_TYPE,
		INTERACTING,
		WALKING,
		JUMPING,
		FALLING,
		LAST_MOTION_TYPE
	};
	enum HorizontalFacing : Uint8 {
		FACING_LEFT,
		FACING_RIGHT
	};
	enum VerticalFacing : Uint8 {
		FORWARD,
		LOOKUP,
		LOOKDOWN
	};
	struct CharState {
		MotionType motionType;
		HorizontalFacing horizontalFacing;
		VerticalFacing verticalFacing;
	};
	//TODO 完善动画状态
	static size_t getState(CharState state) { 
		return state.motionType | (state.horizontalFacing << 3) | (state.verticalFacing << 4);
	}
	const Uint16 MotionSprites = 11;
	const Uint16 CharTypeSprites = 12;
	const float maxVelocityX = 0.15859375f;
	const float maxVelocityY = 0.25f;//需要修正
	const float fiction = 0.00049804687f;
	const float jumpSpeed = maxVelocityY;//为了跳跃对称？？
	const float error = 0.001f;

	const float gravity = 0.0003125f;
	const float stopJumpAccelerate = 3 * gravity;//轻按跳跃后使用这个减慢速度
	const float accelerate = 0.00083007812f;
	const float slowdown = 0.8f;

	const Rectangle CollisionX{ 6, 10, 20, 12 };
	const Rectangle CollisionY{ 10, 2, 12, 30 };


	Player(Graphics& graphics, std::shared_ptr<Map> map, const std::string& filename, Uint16 xPos, Uint16 yPos);
	~Player();

	void setClipRect();
	void setAimator();

	void handleEvent(SDL_Event& e);
	void update(Uint16 deltaTime);
	void updateX(Uint16 deltaTime);
	void updateY(Uint16 deltaTime);
	void updateState();
	void draw(Graphics& graphics);

	void movingLeft();
	void movingRight();
	void stopMoving();

	void startJump();
	void stopJump();

	void lookForward();
	void lookUp();
	void interact();
	
	Rectangle leftCollision(units::Game delta);
	Rectangle rightCollision(units::Game delta);
	Rectangle topCollision(units::Game delta);
	Rectangle bottomCollision(units::Game delta);
private:
	std::shared_ptr<Animation> animation_;
	std::shared_ptr<Animator> animator_;
	std::shared_ptr<Map> map_;

	std::vector<std::vector<SDL_Rect>> clipRects_;
	units::Game xPos_, yPos_;
	units::Game lastXPos_, lastYPos_;
	CharState state_;
	
	bool onGround_;
	bool jumping_;
	bool stopedmoving_ = false;
	float velocityX_, velocityY_;
	float accelerationX_/*, accelerationY_*/;//y的加速度只有重力就行？
};

#endif // !PLAYER_H_