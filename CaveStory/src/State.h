#ifndef STATE_H_
#define STATE_H_

#include "Player.h"

//TODO 
//��Ѷ������Ʒ���״̬ת������֮��
//������ﳯ��״̬

//ѭ���Ĵ�������,������Ҫ��һ�ַ�ʽд? ���������
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
			//�Ͻ�һ��Ļ���Ӧ�����жϸ���Ϊplayer.physics_->velocityY_ > 0
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
		if (player.onGround())//TODO ��Ӵ���animator��ض���
			player.motionState_ = &State::standing;
	}
};

//����״̬ʱ���ֲ��䣬��Ұ������ⰴť���ص��˶�״̬
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