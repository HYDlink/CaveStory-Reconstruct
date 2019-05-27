#include "NumberSprite.h"

using namespace std;
//数字长宽为16px
namespace {
	constexpr const units::Pixel WhiteDigitPosY = 7 * units::HalfTile;
	constexpr const units::Pixel RedDigitPosY = 8 * units::HalfTile;
	constexpr const units::Pixel DigitSize = units::HalfTile;	
	constexpr const units::Pixel SymbolPosX = 4 * units::HalfTile;
	constexpr const units::Pixel SymbolPosY = 6 * units::HalfTile;
	constexpr const int Radix = 10;
}
NumberSprite::NumberSprite(Graphics& graphics, const std::string& filename) {
	for (size_t i = 0; i < Radix; i++) {
		SDL_Rect clip{ i * DigitSize, WhiteDigitPosY, DigitSize, DigitSize };
		whiteDigits_.push_back(make_shared<Sprite>(graphics, filename, clip));
	}
	for (size_t i = 0; i < Radix; i++) {
		SDL_Rect clip{ i * DigitSize, RedDigitPosY, DigitSize, DigitSize };
		redDigits_.push_back(make_shared<Sprite>(graphics, filename, clip));
	}
	SDL_Rect clip{ SymbolPosX, SymbolPosY, DigitSize, DigitSize };
	plus_ = make_shared<Sprite>(graphics, filename, clip);
	clip.x += DigitSize;
	minus_ = make_shared<Sprite>(graphics, filename, clip);
}

//desX为目标对齐位置
void NumberSprite::draw(Graphics& graphics, int num, units::Pixel desX, units::Pixel desY,
	units::Pixel padding, bool showSymbol, bool camIndep, units::ALIGN align) const {
	int digitNum = 0;
	for (int tmp = abs(num); tmp > Radix; tmp /= Radix)
		++digitNum;
	//带有正负号的宽度
	units::Pixel modSize = (DigitSize + padding);
	units::Pixel modWidth = modSize * (showSymbol ? (digitNum + 2) : (digitNum + 1));
	modWidth -= padding;
	units::Pixel currentDesX = units::getAlinedResult(desX, modWidth, align);

	if (showSymbol) {//即使是0也要显示符号
		(num < 0 ? minus_ : plus_)->draw(graphics, currentDesX, desY);
		currentDesX += DigitSize;
	}
	auto &color = (num < 0) ? redDigits_ : whiteDigits_;
	num = abs(num);//置于绝对值，只获得正数来访问color下标
	while (digitNum >= 0) {//从最低位数字（右侧）开始画
		color[num % Radix]->draw(graphics, currentDesX + digitNum * modSize, desY, camIndep);
		num /= Radix;
		--digitNum;
	}
}
