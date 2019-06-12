#include "MainMenu.h"
#include "..//Graphics/SwitchSceneAnimation.h"
#include "..//Graphics/Graphics.h"
#include "..//Utils/Locator.h"
#include <SDL_rect.h>
#include <SDL_pixels.h>

using namespace std;

MainMenu::MainMenu() { init(); sortObjectsByLayer(); }

MainMenu::~MainMenu() {}

void MainMenu::init() {
	shared_ptr<SwitchSceneAnimation> ssa{ make_shared<SwitchSceneAnimation>() };
	camera_ = make_shared<Camera>(Locator<Graphics>::get()->screenRect());
	objects_.emplace_back(ssa);
}
