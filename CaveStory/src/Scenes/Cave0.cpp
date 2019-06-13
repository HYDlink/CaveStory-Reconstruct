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
	shared_ptr<Bat> bat_;
	//…Ë÷√µÿÕº
	shared_ptr<CompleteMap> PrtCave = make_shared<CompleteMap>(*graphics, "PrtCave", "Blue");
	PrtCave->getFgMap()->loadTile(*graphics, "res/PrtCave.bmp", 16, 5);

	numberSprite_ = make_shared<NumberSprite>(*graphics, "res/TextBox.bmp");
	player_ = make_shared<Player>(*graphics, PrtCave->getFgMap(), "res/MyChar.bmp", 240, 240, *numberSprite_);
	bat_ = make_shared<Bat>(*graphics, *player_, "res/NpcCemet.bmp",
		Position2D(units::tileToPixel(3), units::tileToPixel(5)));

#ifdef CSCAMERA
	camera_ = make_shared<CSCamera>(player_);
#else
	camera_ = make_shared<Camera>(graphics->screenRect());
#endif
	camera_->setRestrict(PrtCave->getFgMap()->levelRect());
	graphics->setCamera(camera_);
	objects_.assign({ PrtCave, player_, bat_ });
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
