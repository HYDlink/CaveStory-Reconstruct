#ifndef STATE_H_
#define STATE_H_

#include "Player.h"

//TODO 
//想把动画控制放在状态转换控制之间
//添加人物朝向状态

//循环的大量错误,可能需要换一种方式写? 今天放弃了
class State {
public:
	static StandState standing;
	static WalkingState walking;
	static JumpState jumping;
	static FallState falling;
	static InteractState interacting;

	virtual ~State() {};
	virtual void handleInput(Player& player, Uint8* inputs) = 0;
	virtual void update(Player& player) = 0;
	Player::MotionType type;
};

struct StandState : public State {
	void handleInput(Player& player, Uint8* inputs) {
			player.motionState_ = &State::walking;
		if (inputs[SDL_SCANCODE_K])
			player.motionState_ = &State::jumping;
	}
	void update(Player& player){
		type = Player::STANDING;
		if (!player.onGround()) {
			//严谨一点的话，应当把判断更改为player.physics_->velocityY_ > 0
			if (player.jumping())
				player.motionState_ = &State::jumping;
			else
				player.motionState_ = &State::falling;
		}
	}
};

struct WalkingState : public State {
	void handleInput(Player& player, Uint8* inputs) {
		if (!inputs[SDL_SCANCODE_A] && !inputs[SDL_SCANCODE_D])
			player.motionState_ = &State::standing;
		if (inputs[SDL_SCANCODE_K])
			player.motionState_ = &State::jumping;
	}
	void update(Player& player) {
		type = Player::WALKING;
		standing.update(player);
	}
};

struct JumpState : public State {
	void handleInput(Player& player, Uint8* inputs) {
	}
	void update(Player& player) {
		type = Player::JUMPING;
		if (player.onGround())
			player.motionState_ = &State::standing;
		if (!player.jumping())
			player.motionState_ = &State::falling;
	}
};

struct FallState : public State {
	void handleInput(Player& player, Uint8* inputs) {
	}
	void update(Player& player) {
		type = Player::FALLING;
		if (player.onGround())//TODO 添加触发animator落地动画
			player.motionState_ = &State::standing;
	}
};

//交互状态时保持不变，玩家按下任意按钮返回到运动状态
struct InteractState : public State {
	void handleInput(Player& player, Uint8* inputs) {
		standing.handleInput(player, inputs);
	}
	void update(Player& player) {
		type = Player::INTERACTING;
		standing.update(player);
	}
};

#endif // !STATE_H_