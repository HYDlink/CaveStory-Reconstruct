#pragma once
#include "../Enemy.h"
#include "../units.h"
#include "../Rectangle.h"
class Player;
class Bat : public Enemy {
public:
	using Enemy::animation_;
	const Rectangle damageRect{ 5, 3, 22, 26 };
	Bat(Graphics& graphics, Player& player, const std::string& filename, Position2D pos); 
	Rectangle damageRectangle() const {
		return pos_ + damageRect;
	}
	void setClipRect();
	void update(units::MS deltaTime);
	void draw(Graphics& graphics);
private:
	Player& player_;
	Position2D pos_;
	units::Game centerY_;
	units::Degrees flightAngle_;
	units::Velocity velocityY_;
	HorizontalFacing horizontalFacing_;
	std::vector<SDL_Rect> clipRects_;
};