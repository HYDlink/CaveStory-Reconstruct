#include "Weapon.h"
#include "../Graphics/Animation.h"
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

	// Projectile Sprite
	const units::Tile kProjectileSourceYs[units::MaxGunLevel] = { 2, 2, 3 };
	const units::Tile kHorizontalProjectileSourceXs[units::MaxGunLevel] = { 8, 10, 8 };
	// Projectile Velocity
	const units::Velocity kProjectileSpeed = 0.6f;

	const units::Game kProjectileMaxOffsets[units::MaxGunLevel] =
	{ 7 * units::HalfTile, units::tileToGame(5), units::tileToGame(7) };
	const units::Game kProjectileWidths[units::MaxGunLevel] = { 4.0f, 8.0f, 16.0f };
	const Uint8 kProjectileNums[units::MaxGunLevel] = { 2, 3, 3 };
	const units::MS kProjectileDelay = 200;

	const units::HP kDamages[units::MaxGunLevel] = { 1, 2, 4 };

	const units::GunExperience kExperiences[] = { 0, 10, 30, 40 };
}

//Debug时可以把layer的arms改成foreground，以确定武器贴图位置
Weapon::Weapon(Graphics& graphics, WeaponType type, Player& player): 
	GameObject(LAYER::FOREGROUND), type_(type), player_(player) {
	using namespace units;
	SDL_Rect weaponPos{ gameToPixel(static_cast<uint8_t>(type) * kGunWidth), gameToPixel(kHorizontalOffset),
		gameToPixel(kGunWidth), gameToPixel(kGunHeight) };
	for (int i = 0; i < states ; i++) {
		weapon_sprite_[i] = make_shared<Sprite>(graphics, "res/Arms.bmp", weaponPos);
		weaponPos.y += TileSize;
	}
	SDL_Rect projectilePos{ 0, 0,units::HalfTile, units::HalfTile };
	projectilePos.x = kHorizontalProjectileSourceXs[0];
	projectilePos.y = kProjectileSourceYs[0];
	for (int i = 0; i < 4; i++)	{
		projectile_sprite_[i].reset(new Sprite(graphics, "res/Bullet.bmp", projectilePos));
		projectilePos.x += units::HalfTile;
	}
}

void Weapon::update(units::MS deltaTime) {
	auto objsToRemove = remove_if(children_.begin(), children_.end(),
		[](const shared_ptr<GameObject>& g) { return g->isDead(); });
	children_.erase(objsToRemove, children_.end());

	//测试用，待删除
	for (auto child : children_)
		child->update(deltaTime);
}

void Weapon::draw(Graphics& graphics) const {
	weapon_sprite_[player_.state().faceType()]->draw(graphics, gunX(),
		gunY());
	for (auto child : children_)
		child->draw(graphics);
}

void Weapon::launch() {
	//只允许子弹同时出现特定的数目
	const units::MS currentLaunch = SDL_GetTicks();
	if (currentLaunch - lastLaunch_ < kProjectileDelay)
		return;
	//children.size()代表子弹数量
	if (children_.size() > kProjectileNums[level_])
		return;
	lastLaunch_ = currentLaunch;

	//TODO BUG 即使emplace_back，children.size()依旧为0
	//为什么跳出这个地方，children_的size就变为0了呢，然后回到这里又是3
	shared_ptr<Projectile> tmp(new Projectile
	(player_.pos(), kProjectileSpeed, kProjectileMaxOffsets[level_],
		player_.state(), projectile_sprite_[player_.state().faceType()]));
	children_.emplace_back(tmp);
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
	//1是人物走动的第二帧，这个时候手稍稍提起，然后我们让武器和手贴合住，这个offset是2像素
	if (player_.getAnimation()->getCurFrame() == 1)
		result -= kUpOffset;
	return result;
}

//机枪发出的子弹有随机性，可以传入随机种子
Projectile::Projectile(Position2D pos, units::Velocity vel, units::Game range,
	FaceType faceType, shared_ptr<Sprite> sprite) :
	GameObject(LAYER::ARMS),
	startPos_(pos), pos_(pos), range_(range), vel_(vel, 0),
	faceType_(faceType), sprite_(sprite) {
	if (faceType_.verticalFacing == FORWARD)
		vel_.setAngle((faceType_.horizontalFacing == FACING_RIGHT) ? 0 : 180);
	else
		vel_.setAngle((faceType_.verticalFacing == LOOKDOWN) ? 90 : 360);
	cout << "created a projectile." << endl;
	//添加从武器前部发出的offset
}

Projectile::~Projectile() {
	cout << "deleted a projectile." << endl;
}

void Projectile::update(units::MS deltaTime) {
	pos_.x += vel_.xLen() * deltaTime;
	pos_.y += vel_.yLen() * deltaTime;
	if (abs(pos_.x - startPos_.x) >= range_ || abs(pos_.y - startPos_.y) >= range_)
		isDead_ = true;
}

void Projectile::draw(Graphics& graphics) const {
	sprite_->draw(graphics, pos_.x, pos_.y);
}
