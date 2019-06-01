#pragma once
#include "Scene.h"
#include "..//Graphics/Particle.h"

class ParticleTest :public Scene {
public:
	ParticleTest();
	void init();
	virtual void handleEvent(SDL_Event* e)override {}
};