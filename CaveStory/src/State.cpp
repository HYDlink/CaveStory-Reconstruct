#include "State.h"
#include "Player.h"

StandState* StandState::Instance() {
	static StandState* instance = new StandState();
	return instance;
}

void StandState::handleInput(Player& player, Uint8* inputs) {
	if (inputs[SDL_SCANCODE_K])
		changeState(player, JumpState::Instance());
}

void StandState::update(Player& player) {
	type = Player::STANDING;
	if (!player.onGround()) {
		//严谨一点的话，应当把判断更改为 abs(player.physics_->velocityY_) < 0.01
		if (player.jumping())
			changeState(player, JumpState::Instance());
		else
			changeState(player, FallState::Instance());
	}
}

WalkingState* WalkingState::Instance() {
	static WalkingState* instance = new WalkingState();
	return instance;
}

void WalkingState::handleInput(Player& player, Uint8* inputs) {
	if (!inputs[SDL_SCANCODE_A] && !inputs[SDL_SCANCODE_D])
		changeState(player, StandState::Instance());
	if (inputs[SDL_SCANCODE_K])
		changeState(player, JumpState::Instance());
}

void WalkingState::update(Player& player) {
	type = Player::WALKING;
	StandState::Instance()->update(player);
}

JumpState* JumpState::Instance() {
	static JumpState* instance = new JumpState();
	return instance;
}

void JumpState::handleInput(Player& player, Uint8* inputs) {
}

void JumpState::update(Player& player) {
	type = Player::JUMPING;
	if (player.onGround())
		changeState(player, StandState::Instance());
	if (!player.jumping())
		player.motionState_ = FallState::Instance();
}

FallState* FallState::Instance() {
	static FallState* instance = new FallState();
	return instance;
}

void FallState::handleInput(Player& player, Uint8* inputs) {
}

void FallState::update(Player& player) {
	type = Player::FALLING;
	if (player.onGround())//TODO 添加触发animator落地动画
		changeState(player, StandState::Instance());
}

InteractState* InteractState::Instance() {
	static InteractState* instance = new InteractState();
	return instance;
}

void InteractState::handleInput(Player& player, Uint8* inputs) {
	StandState::Instance()->handleInput(player, inputs);
}

void InteractState::update(Player& player) {
	type = Player::INTERACTING;
	StandState::Instance()->update(player);
}

void State::changeState(Player& player, State* state) {
	player.changeState(state);
}
