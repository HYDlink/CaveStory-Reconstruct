#ifndef STATE_H_
#define STATE_H_
#include <SDL.h>

//TODO 
//��Ѷ������Ʒ���״̬ת������֮��
//������ﳯ��״̬

//ѭ���Ĵ�������,������Ҫ��һ�ַ�ʽд? ���������
//�����޸ĳ�ָ��
class Player;
class State {
public:
	virtual ~State() {};
	virtual void handleInput(Player& player, Uint8* inputs) = 0;
	virtual void update(Player& player) = 0;
	Uint8 type;
protected:
	void changeState(Player& player, State* state);
};

struct StandState : public State {
	static StandState* Instance();
	void handleInput(Player& player, Uint8* inputs);
	void update(Player& player);
	static StandState* instance_;
};

struct WalkingState : public State {
	static WalkingState* Instance();
	void handleInput(Player& player, Uint8* inputs);
	void update(Player& player);
};

struct JumpState : public State {
	static JumpState* Instance();
	void handleInput(Player& player, Uint8* inputs);
	void update(Player& player);
};

struct FallState : public State {
	static FallState* Instance();
	void handleInput(Player& player, Uint8* inputs);
	void update(Player& player);
};

//����״̬ʱ���ֲ��䣬��Ұ������ⰴť���ص��˶�״̬
struct InteractState : public State {
	static InteractState* Instance();
	void handleInput(Player& player, Uint8* inputs);
	void update(Player& player);
};

#endif // !STATE_H_