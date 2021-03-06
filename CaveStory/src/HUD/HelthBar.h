#ifndef HEALTH_BAR_
#define HEALTH_BAR_

#include "../Graphics/Sprite.h"
#include "../Utils/units.h"
#include "../Timer.h"
#include "..//GameObject.h"
//HP
//HPbar白框的位置为48px-126px
class NumberSprite;
class HelathBar : public GameObject{
public:
	HelathBar(Graphics& graphics, const std::string& path, units::HP maxHp
		, NumberSprite& numberSprite);
	void setNumberSprite(NumberSprite& numberSprite);
	void update(units::MS deltaTime) override;
	void draw(Graphics& graphics) const override;
	void takeDamage(units::HP damage);
private:
	void resetFillSprites();
	Timer decreaseTimer_;//HP减少的时候有一段白色区域显示减少的数量
	units::HP maxHp_, currentHp_, damage_;
	Sprite healthBarSprite_;
	VaryWidthSprite healthFillSprite_, damageFillSprite_;
	NumberSprite& numberSprite_;
};

#endif // !HEALTH_BAR_