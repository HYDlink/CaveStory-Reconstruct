#pragma once
#include <string>
#include "../Utils/units.h"
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
	units::Game gunX() const;
	units::Game gunY() const;
private:
	std::shared_ptr<Sprite> weapon_sprite_[states], projectile_sprite_[states];
	Player& player_;
	WeaponType type_;
};