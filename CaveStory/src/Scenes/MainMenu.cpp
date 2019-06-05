#include "MainMenu.h"
#include "..//Graphics/SwitchSceneAnimation.h"
#include "..//Graphics/Graphics.h"
#include "..//Graphics/Animation.h"
#include "..//Utils/Locator.h"
#include <SDL_rect.h>
#include <SDL_pixels.h>

using namespace std;

MainMenu::MainMenu() { init(); sortObjectsByLayer(); }

void MainMenu::init() {
	//32, ¿í512
	const units::Tile xTileNum = 512 / units::TileSize;
	vector<SDL_Rect> clips;
	for (auto i = 0; i < xTileNum; ++i) {
		clips.emplace_back(SDL_Rect{ i * units::TileSize, 0, units::TileSize, units::TileSize });
	}
	Graphics *graphics = Locator<Graphics>::get();
	graphics->setClearColor(SDL_Color{ 255, 255, 255, 255 });
	Animation ani(*graphics, "res/Fadewhite.bmp", std::move(clips));
	shared_ptr<SwitchSceneAnimation> ssa{ make_shared<SwitchSceneAnimation>(ani) };
	camera_ = make_shared<Camera>(Locator<Graphics>::get()->screenRect());
	objects_.emplace_back(ssa);
}
