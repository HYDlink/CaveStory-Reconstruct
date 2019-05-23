#include "HelthBar.h"
namespace {

	// HUD Constants
	const units::Game kHealthBarX = units::tileToGame(1);
	const units::Game kHealthBarY = units::tileToGame(2);
	const units::Game kHealthBarSourceX = 0;
	const units::Game kHealthBarSourceY = 5 * units::HalfTile;
	const units::Game kHealthBarSourceWidth = units::tileToGame(4);
	const units::Game kHealthBarSourceHeight = units::HalfTile;

	const units::Game kHealthFillX = 5 * units::HalfTile;
	const units::Game kHealthFillY = units::tileToGame(2);

	const units::Game kMaxFillWidth = 5 * units::HalfTile - 2.0f;

	const units::Game kHealthDamageSourceX = 0;
	const units::Game kHealthDamageSourceY = units::tileToGame(2);
	const units::Game kHealthDamageSourceHeight = units::HalfTile;


	const units::Game kHealthFillSourceX = 0;
	const units::Game kHealthFillSourceY = 3 * units::HalfTile;
	const units::Game kHealthFillSourceHeight = units::HalfTile;

	const units::Game kHealthNumberX = units::tileToGame(3) / 2;
	const units::Game kHealthNumberY = units::tileToGame(2);
	const int kHealthNumberNumDigits = 2;

	const std::string kSpritePath("TextBox");

	const units::MS kDamageDelay = 1500;

}

HelathBar::HelathBar(Graphics& graphics, const std::string& path,
	units::HP maxHp) :
	healthBarSprite_(graphics, path, 
		SDL_Rect{ units::gameToPixel(kHealthBarSourceX), units::gameToPixel(kHealthBarSourceY),
	  units::gameToPixel(kHealthBarSourceWidth), units::gameToPixel(kHealthBarSourceHeight) }
	), 
	healthFillSprite_(
		graphics, kSpritePath,
		units::gameToPixel(kHealthFillSourceX), units::gameToPixel(kHealthFillSourceY),
		units::gameToPixel(kMaxFillWidth),
		units::gameToPixel(kMaxFillWidth),
		units::gameToPixel(kHealthFillSourceHeight) ),
	damageFillSprite_(
		graphics, kSpritePath,
		units::gameToPixel(kHealthDamageSourceX), units::gameToPixel(kHealthDamageSourceY),
		units::gameToPixel(kMaxFillWidth),
		units::gameToPixel(0),
		units::gameToPixel(kHealthDamageSourceHeight)), 
	maxHp_(maxHp), currentHp_(maxHp), decreaseTimer_(kDamageDelay) {}

void HelathBar::update(units::MS deltaTime) {
	//����ʱ����ɫhp�����٣��԰�ɫ��������ͽ�ɫͬ������
	if (damage_ > 0 && decreaseTimer_.isExpired()) {
		currentHp_ -= damage_;
		damage_ = 0;
	}
}

void HelathBar::draw(Graphics& graphics) {
	healthBarSprite_.draw(graphics, kHealthBarX, kHealthBarY);
	
	if (damage_ > 0) {
		damageFillSprite_.draw(graphics, kHealthFillX, kHealthFillY);
	}

	healthFillSprite_.draw(graphics, kHealthFillX, kHealthFillY);

	//NumberSprite::HUDNumber(graphics, current_health_, kHealthNumberNumDigits).draw(
	//	graphics, kHealthNumberX, kHealthNumberY);
}

void HelathBar::takeDamage(units::HP damage) {
	decreaseTimer_.reset();
	damage_ = damage;
	resetFillSprites();
}

void HelathBar::resetFillSprites() {
	healthFillSprite_.set_percentage_width((currentHp_ - damage_) * 1.0f / maxHp_);
	damageFillSprite_.set_percentage_width(currentHp_ * 1.0f / maxHp_);
}