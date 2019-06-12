#pragma once
#include <string>
#include <vector>
#include "..//GameObject.h"

class Animation;
class Graphics;
class Timer;
class SwitchSceneAnimation : public GameObject{
public:
	SwitchSceneAnimation();
	~SwitchSceneAnimation();
	void update(units::MS deltaTime) override;
	virtual void draw(Graphics& graphics) const override;
private:
	Timer* timer_;
	std::vector<Animation> animations_;
};