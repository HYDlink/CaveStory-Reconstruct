#include "DamageText.h"

namespace {
	constexpr const units::MS FloatTime = 500;
}

DamageText::DamageText(NumberSprite& numberSprite):
	numberSprite_(numberSprite), floatTimer_(FloatTime), 
	numToDisplay_(0), initPosX_(0), initPosY_(0), posX_(0), posY_(0) {}

void DamageText::setPos(Position2D pos) {
	initPosX_ = pos.x;
	initPosY_ = pos.y;
}

void DamageText::active(int numToDisplay) {
	numToDisplay_ = numToDisplay;
	if(!floatTimer_.isActive())
		floatTimer_.reset();
}

void DamageText::update(units::MS deltaTime) {
	posX_ = initPosX_;
	posY_ = initPosY_ - units::HalfTile * floatTimer_.currentTime() / floatTimer_.totalTime();
}

void DamageText::draw(Graphics& graphics) const {
	if(floatTimer_.isActive())
		numberSprite_.draw(graphics, numToDisplay_, posX_, posY_, 1,
			false, units::CENTER_ALIGNED);
}
