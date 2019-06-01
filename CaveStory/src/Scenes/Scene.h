#pragma once

#include "..//GameObject.h"
#include <vector>
#include <memory>

class Map;
class Camera;
class NumberSprite;
class Player;
union SDL_Event;

class Scene {
public:
	Scene() {}
	virtual ~Scene() = default;
	virtual void init() = 0;
	virtual void update(units::MS deltaTime);//用于更新数据
	virtual void handleEvent(SDL_Event* e) = 0;
	virtual void draw(Graphics& graphics) const;
	void sortObjectsByLayer();
	
	std::shared_ptr<Camera> getCamera() { return camera_; }
protected:
	std::vector<std::shared_ptr<GameObject>> objects_;
	std::vector<std::shared_ptr<GameObject>> sortedObjs_;
	std::shared_ptr<Camera> camera_;
	std::shared_ptr<NumberSprite> numberSprite_;
};