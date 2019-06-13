#include "Cave0.h"
#include "../Graphics/Graphics.h"
#include "..//Map.h"
#include "../Backdrop.h"
#include "..//Player.h"
#include "../Enemy.h"
#include "..//Enemys/Bat.h"
#include "..//Utils/Locator.h"
using namespace std;

Cave0::Cave0() { init(); sortObjectsByLayer(); }

void Cave0::init() {
	Graphics* graphics = Locator<Graphics>::get();
	shared_ptr<ForeGround> caveFore_ = make_shared<ForeGround>();
	shared_ptr<FixedBackdrop> caveBd_ = make_shared<FixedBackdrop>(*graphics, "res/bkBlue.bmp");
	shared_ptr<Bat> bat_;
	caveFore_->loadTile(*graphics, "res/PrtCave.bmp", 16, 5);
	caveFore_->loadMapData("res/PrtCave.txt");
	caveFore_->loadCache("res/PrtCave.bmp");
	caveBd_->setSize(*graphics, caveFore_->mapWidth(), caveFore_->mapHeight());
	numberSprite_ = make_shared<NumberSprite>(*graphics, "res/TextBox.bmp");
	player_ = make_shared<Player>(*graphics, caveFore_, "res/MyChar.bmp", 240, 240, *numberSprite_);
	bat_ = make_shared<Bat>(*graphics, *player_, "res/NpcCemet.bmp",
		Position2D(units::tileToPixel(3), units::tileToPixel(5)));

#ifdef CSCAMERA
	camera_ = make_shared<CSCamera>(player_);
#else
	camera_ = make_shared<Camera>(graphics->screenRect());
#endif
	camera_->setRestrict(caveFore_->levelRect());
	graphics->setCamera(camera_);
	objects_.assign({ caveBd_, caveFore_, player_, bat_ });
}

void Cave0::update(units::MS deltaTime) {
#ifndef CSCAMERA
	camera_->follow(player_->centerPos());
#endif
	Scene::update(deltaTime);
}

void Cave0::handleEvent(SDL_Event* e) {
	player_->handleEvent(*e);
}
