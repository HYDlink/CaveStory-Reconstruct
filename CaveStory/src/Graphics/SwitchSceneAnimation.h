#pragma once
#include <string>
#include <vector>
#include "..//GameObject.h"

class Animation;
class Graphics;
class SwitchSceneAnimation : public GameObject{
public:
	SwitchSceneAnimation(const Animation& animaion);
	~SwitchSceneAnimation();
	void update(units::MS deltaTime) override;
	virtual void draw(Graphics& graphics) const override;
private:
	bool expired_;
	std::vector<Animation> animations_;
};