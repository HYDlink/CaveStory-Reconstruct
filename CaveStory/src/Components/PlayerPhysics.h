#ifndef PLAYERPHYSICS_H_
#define PLAYERPHYSICS_H_

#include "PhysicsComponent.h"
#include "PlayerCollision.h"
#include "../Player.h"

//TODO
//�����ײ��������������Ϣ����
//��Ϊ��PlayerCollision�Ĺ��캯���໥�����������ƶ�����һ��Ҫ��ײ�壬���԰�������ײ��Ĳ����ƺ�
class PlayerPhysics :public PhysicsComponent {
	friend class Player;
	friend class PlayerCollision;
public:
	const units::Velocity maxVelocityX = 0.15859375f;
	const units::Velocity maxVelocityY = 0.25f;//��Ҫ����
	const units::Accelration friction = 0.00049804687f;
	const units::Velocity jumpSpeed = maxVelocityY;//Ϊ����Ծ�Գƣ���
	const units::Velocity error = 0.001f;//�ж��ٶ��Ƿ�ӽ�0���������

	const units::Accelration gravity = 0.0003125f;
	const units::Accelration stopJumpAccelerate = 3 * gravity;//�ᰴ��Ծ��ʹ����������ٶ�
	const units::Accelration accelerate = 0.00083007812f;
	const units::Velocity slowdown = 0.8f;

	PlayerPhysics(Player* player, units::Game xPos, units::Game yPos, 
		PlayerCollision* collision = NULL) :
		player_(player), PhysicsComponent(xPos, yPos), onGround_(false), jumping_(false), 
		collision_(collision) {};
	void setCollision(PlayerCollision* collision) { collision_ = collision; }
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
	PlayerCollision* collision_;

	//��Ҫ�Ͷ���״̬���н���
	bool onGround_;
	bool jumping_;
	bool stopedmoving_ = false;
};
#endif // !PLAYERPHYSICS_H_