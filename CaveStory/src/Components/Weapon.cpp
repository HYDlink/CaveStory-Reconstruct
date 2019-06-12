#include "Weapon.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Graphics.h"
#include "../Player.h"

using namespace std;
namespace {
	const int kPolarStarIndex = 2; // 0-based indexing
	const units::Game kGunWidth = units::pixelToGame(3 * units::HalfTile);
	const units::Game kGunHeight = units::pixelToGame(2 * units::HalfTile);

	const units::Tile kHorizontalOffset = 0;
	const units::Tile kUpOffset = 2;
	const units::Tile kDownOffset = 4;

	const units::Tile kLeftOffset = 0;
	const units::Tile kRightOffset = 1;

	const std::string kSpritePath("Arms");

	// Nozzle Offsets
	const units::Game kNozzleHorizontalY = 23;
	const units::Game kNozzleHorizontalLeftX = 10;
	const units::Game kNozzleHorizontalRightX = 38;

	const units::Game kNozzleUpY = 4;
	const units::Game kNozzleUpLeftX = 27;
	const units::Game kNozzleUpRightX = 21;

	const units::Game kNozzleDownY = 28;
	const units::Game kNozzleDownLeftX = 29;
	const units::Game kNozzleDownRightX = 19;

#if 0
	// Projectile Sprite
	const units::Tile kProjectileSourceYs[units::kMaxGunLevel] = { 2, 2, 3 };
	const units::Tile kHorizontalProjectileSourceXs[units::kMaxGunLevel] = { 8, 10, 8 };
	// Projectile Velocity
	const units::Velocity kProjectileSpeed = 0.6f;

	const units::Game kProjectileMaxOffsets[units::kMaxGunLevel] =
	{ 7 * units::HalfTile, units::tileToGame(5), units::tileToGame(7) };
	const units::Game kProjectileWidths[units::kMaxGunLevel] = { 4.0f, 8.0f, 16.0f };

	const units::HP kDamages[units::kMaxGunLevel] = { 1, 2, 4 };

	const units::GunExperience kExperiences[] = { 0, 10, 30, 40 };
#endif
}

//Debug时可以把layer的arms改成foreground，以确定武器贴图位置
Weapon::Weapon(Graphics& graphics, WeaponType type, Player& player): 
	GameObject(LAYER::ARMS), type_(type), player_(player) {
	using namespace units;
	SDL_Rect pos{ gameToPixel(static_cast<uint8_t>(type) * kGunWidth), gameToPixel(kHorizontalOffset),
		gameToPixel(kGunWidth), gameToPixel(kGunHeight) };
	for (int i = 0; i < states ; i++) {
		weapon_sprite_[i] = make_shared<Sprite>(graphics, "res/Arms.bmp", pos);
		pos.y += TileSize;
	}
}

void Weapon::update(units::MS deltaTime) {
}

void Weapon::draw(Graphics& graphics) const {
	weapon_sprite_[player_.state().faceType()]->draw(graphics, gunX(),
		gunY());
}

units::Game Weapon::gunX() const {
	return player_.pos().x -
		(player_.state().horizontalFacing? 0: units::HalfTile);
}

units::Game Weapon::gunY() const {
	units::Game result = player_.pos().y;
	switch (player_.state().verticalFacing) {
	case FORWARD: break;
	case LOOKUP: result -= units::HalfTile / 2;
	case LOOKDOWN: result += units::HalfTile / 2;
	default:
		break;
	}
	return result;
}
