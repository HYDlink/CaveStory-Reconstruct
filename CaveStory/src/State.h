#ifndef STATE_H_
#define STATE_H_
#include <SDL.h>

//TODO 
//想把动画控制放在状态转换控制之间
//添加人物朝向状态

//循环的大量错误,可能需要换一种方式写? 今天放弃了
//尝试修改成指针
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

//交互状态时保持不变，玩家按下任意按钮返回到运动状态
struct InteractState : public State {
	static InteractState* Instance();
	void handleInput(Player& player, Uint8* inputs);
	void update(Player& player);
};

#endif // !STATE_H_