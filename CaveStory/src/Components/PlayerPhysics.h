#ifndef PLAYERPHYSICS_H_
#define PLAYERPHYSICS_H_

#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "../Player.h"

//TODO
//�����ٶ�̫��
//��ײ��������������Ϣ����
//��Ϊ��CollisionComponent�Ĺ��캯���໥�����������ƶ�����һ��Ҫ��ײ�壬���԰�������ײ��Ĳ����ƺ�
class PlayerPhysics :public PhysicsComponent {
	friend class Player;
	friend class CollisionComponent;
public:
	const units::Acceleration friction = 0.00049804687f;
	const units::Velocity jumpSpeed = maxVelocityY_ * 0.8;//Ϊ����Ծ�Գƣ���
	const units::Velocity error = 0.001f;//�ж��ٶ��Ƿ�ӽ�0���������

	const units::Acceleration gravity = 0.0003125f;
	const units::Acceleration stopJumpAccelerate = 3 * gravity;//�ᰴ��Ծ��ʹ����������ٶ�
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

	//��Ҫ�Ͷ���״̬���н���
	bool onGround_;
	bool jumping_;
	bool stopedmoving_ = false;
};
#endif // !PLAYERPHYSICS_H_