#ifndef PLAYER_H_
#define PLAYER_H_

#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"
#include "Rectangle.h"
#include "Map.h"
#include "Timer.h"
#include "HUD/HelthBar.h"
#include "HUD/DamageText.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <tuple>

class PlayerPhysics;
class PlayerCollision;
class Player : public GameObject {
	friend class PlayerPhysics;
	friend class PlayerCollision;
public:
	//TODO 更改为scoped enum, 即enum class MotionType, etc.
	enum MotionType : Uint8 {
		FIRST_MOTION_TYPE,
		STANDING = FIRST_MOTION_TYPE,
		INTERACTING,
		WALKING,
		JUMPING,
		FALLING,
		LAST_MOTION_TYPE
	};
	enum VerticalFacing : Uint8 {
		FORWARD,
		LOOKUP,
		LOOKDOWN
	};
	struct CharState {
		MotionType motionType = STANDING;
		VerticalFacing verticalFacing = FORWARD;
	};
	//TODO 完善动画状态
	static size_t getState(CharState state) { 
		return state.motionType | (state.verticalFacing << 3);
	}
	const units::FPS MotionSprites = 11;
	const units::Frame CharTypeSprites = 6;

	//graphics获取渲染目标, map获取当前地图的碰撞体, filename获取精灵图资源文件位置
	Player(Graphics& graphics, std::shared_ptr<Map> map,
		const std::string& filename, units::Game xPos, units::Game yPos,
		NumberSprite& numberSprite);
	~Player();

	//设置精灵图剪切位置
	void setClipRect();
	void setAimator();
	void setNumberSprite(NumberSprite& numberSprite);

	void handleEvent(SDL_Event& e);
	void update(units::MS deltaTime) override;
	void updateState();
	void updateDebug();
	void draw(Graphics& graphics) const override;

	Position2D pos() const;
	Position2D centerPos() const;
	units::Velocity velX() const;
	units::Velocity velY() const;
	std::vector<Rectangle> collider() const;
	void takeDamage(units::HP damage);

	void lookForward();
	void lookUp();
	void interactOrLookDown();

	bool onGround() const;
	bool jumping() const;
private:
	std::shared_ptr<Animation> animation_;
	std::shared_ptr<Animator> animator_;

	units::HP hp_;
	bool invisible_ = false;
	Timer invisibleTimer_;

	std::vector<std::vector<SDL_Rect>> clipRects_;
	CharState state_, lastState_;
	HorizontalFacing horizontalFacing_; 
	NumberSprite& numberSprite_;
	DamageText damageText_;

	PlayerPhysics* physics_;
	PlayerCollision* collision_;

	HelathBar healthBar_;
};

#endif // !PLAYER_H_