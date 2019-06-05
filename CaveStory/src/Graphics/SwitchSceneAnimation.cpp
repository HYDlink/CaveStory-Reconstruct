#include "SwitchSceneAnimation.h"
#include "Graphics.h"
#include "Animation.h"
#include "..//Utils/units.h"

SwitchSceneAnimation::SwitchSceneAnimation(const Animation& animaion) : expired_(false),
	animations_((units::ScreenWidth / units::HalfTile)* (units::ScreenHeight / units::HalfTile),
	animaion) {
	for (auto& ani : animations_)
		ani.start_Animation(0, 0, 4);
}

SwitchSceneAnimation::~SwitchSceneAnimation() = default;

void SwitchSceneAnimation::update(units::MS deltaTime) {
	for (auto& ani : animations_)
		ani.update();
}

void SwitchSceneAnimation::draw(Graphics& graphics) const {
	for (size_t i = 0; i < animations_.size(); i++) {
		SDL_Rect tmp{
			(i % units::ScreenTileWidth) * units::TileSize,
			(i / units::ScreenTileWidth) * units::TileSize,
			units::TileSize,
			units::TileSize
		};
		animations_[i].draw(graphics, &tmp);
	}
}
