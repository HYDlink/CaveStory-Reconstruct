#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <tuple>

#include "Animation.h"
#include "Animator.h"
#include "Rectangle.h"
#include "State.h"
#include "Map.h"

class PlayerPhysics;
class PlayerCollision;
class Player {
	friend class PlayerPhysics;
	friend class PlayerCollision;
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

	Player(Graphics& graphics, std::shared_ptr<Map> map, const std::string& filename, units::Game xPos, units::Game yPos);
	~Player();

	void setClipRect();
	void setAimator();

	void handleEvent(SDL_Event& e);
	void update(units::MS deltaTime);
	void updateState();
	void updateDebug();
	void draw(Graphics& graphics);

	void lookForward();
	void lookUp();
	void interactOrLookDown();

	bool onGround() const;
	bool jumping() const;

	//因为所有的State派生类都要写motionState_, 而这样会造成大量的友元声明(因为友元关系不会继承)
	//public是暂时的解决方法
	State* motionState_;
private:
	std::shared_ptr<Animation> animation_;
	std::shared_ptr<Animator> animator_;
	std::shared_ptr<Map> map_;

	std::vector<std::vector<SDL_Rect>> clipRects_;
	CharState state_, lastState_;

	PlayerPhysics* physics_;
	PlayerCollision* collision_;
};

#endif // !PLAYER_H_