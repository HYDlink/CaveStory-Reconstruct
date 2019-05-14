#ifndef PLAYER_H_
#define PLAYER_H_

#include "Animation.h"
#include "Animator.h"
#include <vector>
#include <memory>
#include <algorithm>

class Player {
public:
	enum MotionType {
		FIRST_MOTION_TYPE,
		STANDING = FIRST_MOTION_TYPE,
		INTERACTING,
		WALKING,
		JUMPING,
		FALLING,
		LAST_MOTION_TYPE
	};
	enum FaceType {
		FACING_LEFT,
		FACING_RIGHT
	};
	static size_t getState(MotionType mt, FaceType ft) { return mt + ft * 10; }
	const Uint16 MotionSprites = 11;
	const Uint16 CharTypeSprites = 12;
	const float maxVelocityX = 3;
	const float maxVelocityY = 3;
	const float jumpSpeed = maxVelocityY;//为了跳跃对称？？

	const float gravity = 0.1f;
	const float stopJumpAccelerate = 0.2f;//轻按跳跃后使用这个减慢速度
	const float accelerate = 0.1f;
	const float slowdown = 0.8f;


	Player(Graphics& graphics, const std::string& filename, Uint16 xPos, Uint16 yPos);
	~Player();

	void setClipRect();
	void setAimator();
	void handleEvent(SDL_Event& e);
	void update();
	void updateX();
	void updateY();
	void draw(Graphics& graphics);

	void movingLeft();
	void movingRight();
	void stopMoving();

	void startJump();
	void stopJump();

	void lookUp();
private:
	std::shared_ptr<Animation> animation_;
	std::shared_ptr<Animator> animator_;
	std::vector<std::vector<SDL_Rect>> clipRects_;
	Uint16 xPos_, yPos_;

	FaceType currentFacing_ = FACING_RIGHT;
	bool onGround_;
	bool jumping_;
	float velocityX_, velocityY_;
	float accelerationX_/*, accelerationY_*/;//y的加速度只有重力就行？
};

#endif // !PLAYER_H_