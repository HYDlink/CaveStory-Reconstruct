#pragma once
#include "../Enemy.h"
#include "../Utils/units.h"
#include "../Rectangle.h"
class Player;
class NumberSprite;
class Bat : public Enemy, public GameObject {
public:
	using Enemy::animation_;
	const Rectangle damageRect{ 5, 3, 22, 26 };
	Bat(Graphics& graphics, Player& player, const std::string& filename, Position2D pos); 
	//void setNumberSprite(NumberSprite& numberSprite);
	Rectangle damageRectangle() const {
		return pos_ + damageRect;
	}
	void setClipRect();
	void update(units::MS deltaTime) override;
	virtual void draw(Graphics& graphics) const override;
private:
	Player& player_;
	Position2D pos_;
	units::Game centerY_;
	units::Degrees flightAngle_;
	units::Velocity velocityY_;
	HorizontalFacing horizontalFacing_;
	std::vector<SDL_Rect> clipRects_;
};