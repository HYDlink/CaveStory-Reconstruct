#pragma once

#include "Scene.h"
#include "../Graphics/Graphics.h"

class Cave0 final : public Scene {
public:
	Cave0();
	~Cave0() = default;
	void init();
	virtual void update(units::MS deltaTime) override;
	virtual void handleEvent(SDL_Event* e) override;
private:
	std::shared_ptr<Player> player_;
};