#pragma once
#include "Scene.h"

class MainMenu : public Scene {
public:
	MainMenu();
	void init();
	virtual void handleEvent(SDL_Event* e)override {}
};