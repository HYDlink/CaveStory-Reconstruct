#include "Sprite.h"


Sprite::Sprite(Graphics& graphics, const std::string& path, TransparentColor color)
	: Sprite(graphics, path, SDL_Rect(), color) {}

Sprite::Sprite(Graphics& graphics, const std::string& filename, const SDL_Rect& clip, TransparentColor color) {
	reset(graphics, filename, color, clip);
}

Sprite::~Sprite() {
	reset();
}

void Sprite::reset() {
	if (texture_ != NULL) {
		//不destroyTexture，因为Texture是从Graphic中共享得到的
		texture_ = NULL;
		srcPos_ = SDL_Rect();
	}
}

void Sprite::reset(Graphics& graphics, const std::string& filename, 
	TransparentColor color, const SDL_Rect& clip) {
	reset();
	transparentColor_ = color;
	texture_ = graphics.loadFromFile(filename, transparentColor_);
	srcPos_ = clip;
	if (srcPos_ == SDL_Rect()) {
		uint32_t format;
		int access, w, h;
		SDL_QueryTexture(texture_, &format, &access, &w, &h);
		srcPos_.w = w;
		srcPos_.h = h;
	}
}

/*
* \brief 剪切一定区域然后绘制到屏幕上的位置
* \param srcPos  Sprite载入的texture的剪切位置，或设置NULL来使用Sprite内置的剪切位置
* \param dstPos  Sprite绘制到屏幕上的位置，只需要位置不需要长宽
*/
void Sprite::draw(Graphics& graphics, const SDL_Rect* srcPos, const SDL_Rect* dstPos,
	bool camIndep, const SDL_RendererFlip flip) const {
	graphics.render(texture_, srcPos? srcPos : &srcPos_, dstPos, camIndep, flip);
}

void Sprite::draw(Graphics& graphics, units::Pixel desX, units::Pixel desY,
	bool camIndep, const SDL_RendererFlip flip) const {
	SDL_Rect dstPos{ desX, desY, 0, 0 };
	graphics.render(texture_, &srcPos_, &dstPos, camIndep, flip);
}

bool operator==(const SDL_Rect & lhs, const SDL_Rect & rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h);
}