#pragma once

#include "..//Timer.h"
#include "..//GameObject.h"

class NumberSprite;
class DamageText : public GameObject{
public:
	DamageText(NumberSprite& numberSprite);
	void setPos(Position2D pos);
	void active(int numToDisplay);
	void update(units::MS deltaTime) override;
	void draw(Graphics& graphics) const override;
private:
	NumberSprite& numberSprite_;
	Timer floatTimer_;
	int numToDisplay_;
	units::Game initPosX_, initPosY_, posX_, posY_;
};