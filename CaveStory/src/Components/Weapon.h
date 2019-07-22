#pragma once
#include <string>
#include <SDL_timer.h>
#include "../Utils/units.h"
#include "../Utils/FacingType.h"
#include "../Utils/PolarVector.h"
#include "../GameObject.h"

constexpr const uint8_t states = 6;
enum class WeaponType:uint8_t {
	NONE,
	SNAKE,
	POLARSTAR,
	FIREBALL,
	MACHINEGUN,
	MISSLE, //朝上的时候需要调整x轴位置
	BUBBLE = MISSLE + 2,//贴图中间莫名奇妙的几个空位
	KNIFE,
	SUPER_MISSLE = BUBBLE + 3,
	NEMESIS,
	SPUR //这个的贴图位于最下方需要调整
};
class Sprite;
class Player;
class Weapon : public GameObject{
public:
	Weapon(Graphics& graphics, WeaponType type, Player& player);
	void update(units::MS deltaTime) override;
	void draw(Graphics& graphics) const override;
	void launch(); // 发射子弹
	units::Game gunX() const;
	units::Game gunY() const;
private:
	std::shared_ptr<Sprite> weapon_sprite_[states], projectile_sprite_[4];
	Player& player_;
	WeaponType type_;
	units::GunLevel level_ = 0;
	units::MS lastLaunch_ = 0;
};

class Projectile: public GameObject {
public:
	//TODO 使用Animation而不是Sprite，有些子弹是动画
	Projectile(Position2D pos, units::Velocity vel, units::Game range,  
		FaceType faceType, std::shared_ptr<Sprite> sprite);
	~Projectile();
	void update(units::MS deltaTime) override;
	void draw(Graphics& graphics) const override;
private:
	PolarVector<units::Game> vel_;
	Position2D startPos_;
	Position2D pos_;
	units::Game range_; // 射程
	FaceType faceType_;
	std::shared_ptr<Sprite> sprite_;
};