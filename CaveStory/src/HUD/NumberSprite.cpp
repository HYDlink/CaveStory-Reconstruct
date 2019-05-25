#include "NumberSprite.h"

using namespace std;
//数字长宽为16px
namespace {
	constexpr const units::Pixel WhiteDigitPosY = 7 * units::HalfTile;
	constexpr const units::Pixel RedDigitPosY = 8 * units::HalfTile;
	constexpr const units::Pixel DigitSize = units::HalfTile;	
	constexpr const units::Pixel SymbolPosX = 4 * units::HalfTile;
	constexpr const units::Pixel SymbolPosY = 6 * units::HalfTile;
}
NumberSprite::NumberSprite(Graphics& graphics, const std::string& filename) {
	for (size_t i = 0; i < 10; i++) {
		SDL_Rect clip{ i * DigitSize, WhiteDigitPosY, DigitSize, DigitSize };
		whiteDigits_.push_back(make_shared<Sprite>(graphics, filename, clip));
	}
	for (size_t i = 0; i < 10; i++) {
		SDL_Rect clip{ i * DigitSize, RedDigitPosY, DigitSize, DigitSize };
		whiteDigits_.push_back(make_shared<Sprite>(graphics, filename, clip));
	}
	SDL_Rect clip{ SymbolPosX, SymbolPosY, DigitSize, DigitSize };
	plus_ = make_shared<Sprite>(graphics, filename, clip);
	clip.x += DigitSize;
	minus_ = make_shared<Sprite>(graphics, filename, clip);
}

//desX为目标对齐位置
void NumberSprite::draw(Graphics& graphics, int num, units::Pixel desX, units::Pixel desY,
	units::Pixel padding, bool showSymbol, units::ALIGN align) const {
	Uint8 digitNum = 1;
	for (int tmp = num; tmp > 10; tmp /= 10)
		++digitNum;
	//带有正负号的宽度
	units::Pixel modWidth = DigitSize * (showSymbol ? (digitNum + 1) : digitNum);
	units::Pixel currentDesX = units::getAlinedResult(desX, modWidth, align);

	if (showSymbol) {//即使是0也要显示符号
		(num < 0 ? minus_ : plus_)->draw(graphics, currentDesX, desY);
		currentDesX += DigitSize;
	}
	auto &color = (num < 0) ? redDigits_ : whiteDigits_;
	while (digitNum > 0) {
		color[num % 10]->draw(graphics, currentDesX, desY);
		currentDesX += DigitSize;
		num /= 10;
		--digitNum;
	}
}
