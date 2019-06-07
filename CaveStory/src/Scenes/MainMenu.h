#pragma once
#include "Scene.h"

class Animation;
class MainMenu : public Scene {
public:
	MainMenu();
	~MainMenu();
	void init();
	virtual void handleEvent(SDL_Event* e)override {}
private:
};