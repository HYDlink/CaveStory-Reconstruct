#include "CSCamera.h"
#include "Player.h"
#include "Math.h"

namespace {
	const units::Velocity maxVelocityX = 0.15859375f;
}

CSCamera::CSCamera() = default;

CSCamera::CSCamera(std::shared_ptr<Player> player): 
	Camera(player->centerPos()), player_(player), velX(0) {}

void CSCamera::setPlayer(std::shared_ptr<Player> player) { player_ = player; }

// TODO 根据角色转向改变位置
void CSCamera::update(units::MS deltaTime) {
//	units::Game x = SmoothDamp(curPos_.x, player_->centerPos().x, velX,
//		4, deltaTime, maxVelocityX);
	units::Game x = SmoothDamp(curPos_.x, player_->centerPos().x, velX,
		0.01f, float(deltaTime)/1000);
	x += velX * deltaTime;
	auto tmpView = viewPort_;
	tmpView.setLeft(x - tmpView.width() / 2);
	restrict(tmpView);
}
