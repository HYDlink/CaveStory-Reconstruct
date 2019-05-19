#pragma once
#include "Player.h"

//TODO 
//想把动画控制放在状态转换控制之间
//添加人物朝向状态
class State {
public:
	static StandState standing;
	static WalkingState walking;
	static JumpState jumping;
	static FallState falling;
	static InteractState interacting;

	virtual ~State() {};
	virtual void handleInput(Player& player, Uint8* inputs) = 0;
	const State* currentState() const { return state_; }
	virtual void update(Player& player) = 0;
protected:
	State* state_;
};

class StandState : public State {
	void handleInput(Player& player, Uint8* inputs) {
		if (inputs[SDL_SCANCODE_A] || inputs[SDL_SCANCODE_D])
			state_ = &State::walking;
		if (inputs[SDL_SCANCODE_K])
			state_ = &State::jumping;
	}
	void update(Player& player){
	}
};

class WalkingState : public State {
	void handleInput(Player& player, Uint8* inputs) {
		if (!inputs[SDL_SCANCODE_A] && !inputs[SDL_SCANCODE_D])
			state_ = &State::standing;
		if (inputs[SDL_SCANCODE_K])
			state_ = &State::jumping;
	}
	void update(Player& player) {
	}
};

class JumpState : public State {
	void handleInput(Player& player, Uint8* inputs) {
	}
	void update(Player& player) {
		if (player.onGround())
			state_ = &State::standing;
	}
};

class FallState : public State {
	void handleInput(Player& player, Uint8* inputs) {
	}
	void update(Player& player) {
		if (player.onGround())
			state_ = &State::standing;
	}
};

class InteractState : public State {
	void handleInput(Player& player, Uint8* inputs) {
	}
	void update(Player& player) {
	}
};
#pragma once
