#ifndef PLAYERPHYSICS_H_
#define PLAYERPHYSICS_H_

#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "../Player.h"

//TODO
//降落速度太慢
//碰撞检测组件，进行信息传递
//因为和CollisionComponent的构造函数相互依赖，但是移动并不一定要碰撞体，所以把设置碰撞体的步骤移后
class PlayerPhysics :public PhysicsComponent {
	friend class Player;
	friend class CollisionComponent;
public:
	const units::Acceleration friction = 0.00049804687f;
	const units::Velocity jumpSpeed = maxVelocityY_ * 0.8;//为了跳跃对称？？
	const units::Velocity error = 0.001f;//判断速度是否接近0的允许误差

	const units::Acceleration gravity = 0.0003125f;
	const units::Acceleration stopJumpAccelerate = 3 * gravity;//轻按跳跃后使用这个减慢速度
	const units::Acceleration accelerate = 0.00083007812f;
	const units::Velocity slowdown = 0.8f;

	PlayerPhysics(Player* player, units::Game xPos, units::Game yPos, 
		CollisionComponent * collision = nullptr);;
	void setCollision(CollisionComponent* collision) { collision_ = collision; }
	void handleInput(const Uint8* inputs);
	void update(units::MS deltaTime);
	void updateX(units::MS deltaTime);
	void updateY(units::MS deltaTime);

	void movingLeft();
	void movingRight();
	void stopMoving();

	void startJump();
	void stopJump();
private:
	Player* player_;
	CollisionComponent* collision_;

	//需要和动画状态进行交互
	bool onGround_;
	bool jumping_;
	bool stopedmoving_ = false;
};
#endif // !PLAYERPHYSICS_H_