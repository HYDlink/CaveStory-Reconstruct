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
		MotionType motionType = STANDING;
		HorizontalFacing horizontalFacing = FACING_LEFT;
		VerticalFacing verticalFacing = FORWARD;
	};
	//TODO 完善动画状态
	static size_t getState(CharState state) { 
		return state.motionType | (state.horizontalFacing << 3) | (state.verticalFacing << 4);
	}
	const units::FPS MotionSprites = 11;
	const units::Frame CharTypeSprites = 12;
	const units::Velocity maxVelocityX = 0.15859375f;
	const units::Velocity maxVelocityY = 0.25f;//需要修正
	const units::Accelration fiction = 0.00049804687f;
	const units::Velocity jumpSpeed = maxVelocityY;//为了跳跃对称？？
	const units::Velocity error = 0.001f;//判断速度是否接近0的允许误差

	const units::Accelration gravity = 0.0003125f;
	const units::Accelration stopJumpAccelerate = 3 * gravity;//轻按跳跃后使用这个减慢速度
	const units::Accelration accelerate = 0.00083007812f;
	const units::Velocity slowdown = 0.8f;

	const Rectangle CollisionX{ 6, 10, 20, 12 };
	const Rectangle CollisionY{ 10, 2, 12, 30 };


	Player(Graphics& graphics, std::shared_ptr<Map> map, const std::string& filename, units::Game xPos, units::Game yPos);
	~Player();

	void setClipRect();
	void setAimator();

	void handleEvent(SDL_Event& e);
	void update(units::MS deltaTime);
	void updateX(units::MS deltaTime);
	void updateY(units::MS deltaTime);
	void updateState();
	void updateDebug();
	void draw(Graphics& graphics);

	void movingLeft();
	void movingRight();
	void stopMoving();

	void startJump();
	void stopJump();

	void lookForward();
	void lookUp();
	void interactOrLookDown();

	
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
	CharState state_, lastState_;
	
	bool onGround_;
	bool jumping_;
	bool stopedmoving_ = false;
	units::Velocity velocityX_, velocityY_;
	units::Accelration accelerationX_/*, accelerationY_*/;//y的加速度只有重力就行？
};

#endif // !PLAYER_H_