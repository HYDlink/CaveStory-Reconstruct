#include "ParticleTest.h"
#include "..//Utils/Locator.h"
#include "..//Graphics/ParticleGroup.h"
#include <memory>

using namespace std;

ParticleTest::ParticleTest() { init(); sortObjectsByLayer(); }

void ParticleTest::init() {
	Position2D pos{ 240, 240 };
	shared_ptr<GameObject> pg = make_shared<ParticleGroup<100>>(pos, 50, 1000);
	SDL_Rect clip{ 0, 64, 32, 32 };
	//particle->loadSprite(*Locator<Graphics>::get(), "res/Caret.bmp", clip);
	camera_ = make_shared<Camera>( Locator<Graphics>::get()->screenRect());
	objects_.push_back(pg);
}