#include "CSCamera.h"
#include "Player.h"
#include "Utils/Math.h"
#include "Components/PhysicsComponent.h"

//TODO
//���ʵ�֣�
//�Խ�ɫΪ�����λ�ã������ɫ���ٶ�Ϊ��ɫ������ٶȣ�ת��ı�
//�ٶ����ֵΪQuote�ٶȣ�������Quote��Quote�𲽺��ٶ�������Quoteͣ�����ٶȼ���
namespace {
	const units::Velocity maxVelocityX = 0.15859375f;
	const units::Game FacingOffset = 100;
	const units::Velocity CameraLerpVel = 0.01;
}

CSCamera::CSCamera() = default;

CSCamera::CSCamera(std::shared_ptr<Player> player): 
	Camera(player->centerPos()), player_(player), velX(0) {}

void CSCamera::setPlayer(std::shared_ptr<Player> player) { player_ = player; }

// TODO ���ݽ�ɫת��ı�λ��
void CSCamera::update(units::MS deltaTime) {
	units::Game targetX = player_->centerPos().x +
		(player_->state().horizontalFacing == FACING_RIGHT ? FacingOffset : -FacingOffset);
	curPos_.x = lerp(curPos_.x, targetX, CameraLerpVel*(1 + 2 * player_->velX()));
	curPos_.x += velX * deltaTime;
	auto tmpView = viewPort_;
	tmpView.setLeft(curPos_.x - tmpView.width() / 2);
	restrict(tmpView);
}
