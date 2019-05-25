#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include "..//Sprite.h"
#include "..//units.h"

#include <vector>
#include <memory>

//两种颜色的数字，红色代表减少值，比如-3hp，白色代表加值
//作为单体创建？因为数字的资源是独一的
//绘画时使用padding描述间距
//使用三种对齐方式，对齐的描述保存在units里面
//添加正负数
class NumberSprite {
public:
	NumberSprite(Graphics& graphics, const std::string& filename);
	void draw(Graphics& graphics, int num, units::Pixel desX, units::Pixel desY,
		units::Pixel padding = 0, bool showSymbol = false, 
		units::ALIGN align = units::LEFT_ALIGNED) const;
private:
	std::vector<std::shared_ptr<Sprite>> whiteDigits_;
	std::vector<std::shared_ptr<Sprite>> redDigits_;
	std::shared_ptr<Sprite> plus_;
	std::shared_ptr<Sprite> minus_;
};

#endif // !NUMBER_SPRITE_H_