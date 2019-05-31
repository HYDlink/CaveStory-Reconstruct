#include "CSCamera.h"
#include "Player.h"
#include "Math.h"

//TODO
//相机实现：
//以角色为父相对位置，跟随角色，速度为角色的相对速度，转向改变
//速度最大值为Quote速度，并紧跟Quote，Quote起步后速度上升，Quote停步后速度减慢
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
//	std::cout << deltaTime << " " << float(deltaTime) / 1000 << std::endl;
	units::Game x = SmoothDamp(curPos_.x, player_->centerPos().x, velX,
		0.1f, float(deltaTime)/1000);
	x += velX * deltaTime;
	auto tmpView = viewPort_;
	tmpView.setLeft(x - tmpView.width() / 2);
	restrict(tmpView);
}
