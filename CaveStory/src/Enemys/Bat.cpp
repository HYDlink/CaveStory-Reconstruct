#include "Bat.h"
#include "../Player.h"
#include "../HUD/NumberSprite.h"

using namespace std;

namespace {
	const units::Frame kNumFlyFrames = 3;
	const units::FPS kFlyFps = 13;

	const units::AngularVelocity kAngularVelocity = 120.0f / 1000.0f;

	const units::Game kFlightAmplitude = 5 * units::HalfTile;
	const units::HP kContactDamage = 1;
}

Bat::Bat(Graphics& graphics, Player& player, const std::string& filename, Position2D pos):
    Enemy(graphics, filename), player_(player), flightAngle_(0), pos_(pos), centerY_(pos.y){
	setClipRect();
	animation_->setFrames(clipRects_);
	animation_->start_Animation(0, 2, 6, true);
}

//只截了空闲飞行的3个图像
void Bat::setClipRect() {
	//左朝向
	for (auto i = 0; i < kNumFlyFrames; ++i)
		clipRects_.push_back(SDL_Rect
			{ units::tileToPixel(2 + i), units::tileToPixel(2), units::TileSize, units::TileSize });
	//右朝向
	for (auto i = 0; i < kNumFlyFrames; ++i)
		clipRects_.push_back(SDL_Rect
			{ units::tileToPixel(2 + i), units::tileToPixel(3), units::TileSize, units::TileSize });
}

//根据时间类似钟摆一样上下移动
void Bat::update(units::MS deltaTime) {
	flightAngle_ += kAngularVelocity * deltaTime;
	pos_.y = centerY_ + kFlightAmplitude * units::sin(flightAngle_);

	if (damageRectangle().collidesWith(player_.collider()))
		player_.takeDamage(kContactDamage);
	animation_->update();
}

void Bat::draw(Graphics& graphics, const NumberSprite& numberSprite) const {
	SDL_Rect pos{ pos_.x, pos_.y, 0, 0 };
	animation_->draw(graphics, &pos);
}
