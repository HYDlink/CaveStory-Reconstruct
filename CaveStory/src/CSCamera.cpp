#include "CSCamera.h"
#include "Player.h"
#include "Math.h"

//TODO
//���ʵ�֣�
//�Խ�ɫΪ�����λ�ã������ɫ���ٶ�Ϊ��ɫ������ٶȣ�ת��ı�
//�ٶ����ֵΪQuote�ٶȣ�������Quote��Quote�𲽺��ٶ�������Quoteͣ�����ٶȼ���
namespace {
	const units::Velocity maxVelocityX = 0.15859375f;
}

CSCamera::CSCamera() = default;

CSCamera::CSCamera(std::shared_ptr<Player> player): 
	Camera(player->centerPos()), player_(player), velX(0) {}

void CSCamera::setPlayer(std::shared_ptr<Player> player) { player_ = player; }

// TODO ���ݽ�ɫת��ı�λ��
void CSCamera::update(units::MS deltaTime) {
//	units::Game x = SmoothDamp(curPos_.x, player_->centerPos().x, velX,
//		4, deltaTime, maxVelocityX);
//	std::cout << deltaTime << " " << float(deltaTime) / 1000 << std::endl;
	units::Game x = SmoothDamp(curPos_.x, player_->centerPos().x, velX,
		0.1f, float(deltaTime)/1000);
	x += velX * deltaTime;
	auto tmpView = viewPort_;
	tmpView.setLeft(x - tmpView.width() / 2);
	restrict(tmpView);
}
