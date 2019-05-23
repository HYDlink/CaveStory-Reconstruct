#ifndef HEALTH_BAR_
#define HEALTH_BAR_

#include "../Sprite.h"
#include "../units.h"
#include "../Timer.h"
//HP
//HPbar�׿��λ��Ϊ48px-126px
class HelathBar {
public:
	HelathBar(Graphics& graphics, const std::string& path, units::HP maxHp);
	void update(units::MS deltaTime);
	void draw(Graphics& graphics);
	void takeDamage(units::HP damage);
private:
	void resetFillSprites();
	Timer decreaseTimer_;//HP���ٵ�ʱ����һ�ΰ�ɫ������ʾ���ٵ�����
	units::HP maxHp_, currentHp_, damage_;
	Sprite healthBarSprite_;
	VaryWidthSprite healthFillSprite_, damageFillSprite_;
};

#endif // !HEALTH_BAR_