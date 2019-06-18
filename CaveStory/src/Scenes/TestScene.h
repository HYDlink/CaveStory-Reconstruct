#pragma once
#include "Scene.h"

class TestScene : public Scene {
public:
	TestScene();
	~TestScene() = default;
	void init() override;
	virtual void update(units::MS deltaTime) override;
	virtual void handleEvent(SDL_Event* e) override;
private:
	std::shared_ptr<Player> player_;
};