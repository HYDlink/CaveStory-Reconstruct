#include "SwitchSceneAnimation.h"
#include "Graphics.h"
#include "Animation.h"
#include "..//Utils/Locator.h"
#include "..//Utils/units.h"
#include "..//Timer.h"

using namespace units;
using namespace std;

SwitchSceneAnimation::SwitchSceneAnimation() {
	//32, ¿í512
	const units::Tile xTileNum = 512 / units::TileSize;
	vector<SDL_Rect> clips;
	for (auto i = 0; i < xTileNum; ++i) {
		clips.emplace_back(SDL_Rect{ i * units::TileSize, 0, units::TileSize, units::TileSize });
	}
	Graphics* graphics = Locator<Graphics>::get();
	graphics->setClearColor(SDL_Color{ 255, 255, 255, 255 });
	Animation ani(*graphics, "res/Fadewhite.bmp", std::move(clips), TransparentColor::WHITE);
	animations_.assign((ScreenTileWidth) * (ScreenTileHeight),
		ani);
	timer_ = new Timer(50, true);
}

SwitchSceneAnimation::~SwitchSceneAnimation() = default;

void SwitchSceneAnimation::update(MS deltaTime) {
	static auto i = 0;
	size_t j;
	if (timer_->isExpired() && i < ScreenTileWidth) {
		timer_->reset();
		for (j = 0; j < ScreenTileHeight; j++) {
			animations_[i + j * ScreenTileWidth].start_Animation(-1, -1, 2);
		}
		++i;
	}
	if (animations_[ScreenTileWidth - 1].isStopped())
		isDead_ = true;
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
