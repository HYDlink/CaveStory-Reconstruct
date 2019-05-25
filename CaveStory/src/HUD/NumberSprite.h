#ifndef NUMBER_SPRITE_H_
#define NUMBER_SPRITE_H_

#include "..//Sprite.h"
#include "..//units.h"

#include <vector>
#include <memory>

//������ɫ�����֣���ɫ�������ֵ������-3hp����ɫ�����ֵ
//��Ϊ���崴������Ϊ���ֵ���Դ�Ƕ�һ��
//�滭ʱʹ��padding�������
//ʹ�����ֶ��뷽ʽ�����������������units����
//���������
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