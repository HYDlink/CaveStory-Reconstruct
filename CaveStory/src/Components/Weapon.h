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
	MISSLE, //���ϵ�ʱ����Ҫ����x��λ��
	BUBBLE = MISSLE + 2,//��ͼ�м�Ī������ļ�����λ
	KNIFE,
	SUPER_MISSLE = BUBBLE + 3,
	NEMESIS,
	SPUR //�������ͼλ�����·���Ҫ����
};
class Sprite;
class Player;
class Weapon : public GameObject{
public:
	Weapon(Graphics& graphics, WeaponType type, Player& player);
	void update(units::MS deltaTime) override;
	void draw(Graphics& graphics) const override;
	void launch(); // �����ӵ�
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
	//TODO ʹ��Animation������Sprite����Щ�ӵ��Ƕ���
	Projectile(Position2D pos, units::Velocity vel, units::Game range,  
		FaceType faceType, std::shared_ptr<Sprite> sprite);
	~Projectile();
	void update(units::MS deltaTime) override;
	void draw(Graphics& graphics) const override;
private:
	PolarVector<units::Game> vel_;
	Position2D startPos_;
	Position2D pos_;
	units::Game range_; // ���
	FaceType faceType_;
	std::shared_ptr<Sprite> sprite_;
};