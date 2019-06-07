#include "SwitchSceneAnimation.h"
#include "Graphics.h"
#include "Animation.h"
#include "..//Utils/units.h"
#include "..//Timer.h"

using namespace units;
using namespace std;

SwitchSceneAnimation::SwitchSceneAnimation(const Animation& animaion) : expired_(false),
	animations_((ScreenTileWidth)* (ScreenTileHeight),
	animaion) {
	timer_ = new Timer(50, true);
}

SwitchSceneAnimation::~SwitchSceneAnimation() = default;

void SwitchSceneAnimation::update(MS deltaTime) {
	static auto i = 0;
	if (timer_->isExpired() && i < ScreenTileWidth) {
		timer_->reset();
		for (size_t j = 0; j < ScreenTileHeight; j++) {
			animations_[i + j * ScreenTileWidth].start_Animation(-1, -1, 2);
		}
		++i;
		if (i >= ScreenTileWidth) expired_ = true;
	}
	for (auto& ani : animations_)
		ani.update();
}

void SwitchSceneAnimation::draw(Graphics& graphics) const {
	for (size_t i = 0; i < animations_.size(); i++) {
		SDL_Rect tmp{
			(i % ScreenTileWidth) * TileSize,
			(i / ScreenTileWidth) * TileSize,
			TileSize,
			TileSize
		};
		animations_[i].draw(graphics, &tmp);
	}
}
