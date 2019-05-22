#include "Sprite.h"


Sprite::Sprite(Graphics& graphics, const std::string& path)
	: Sprite(graphics, path, SDL_Rect()) {}

Sprite::Sprite(Graphics& graphics, const std::string& filename, const SDL_Rect& clip) {
	reset(graphics, filename, clip);
}

Sprite::~Sprite() {
	reset();
}

void Sprite::reset() {
	if (texture_ != NULL) {
		SDL_DestroyTexture(texture_);
		texture_ = NULL;
		srcPos_ = SDL_Rect();
	}
}

void Sprite::reset(Graphics& graphics, const std::string& filename, const SDL_Rect& clip) {
	reset();
	texture_ = graphics.loadFromFile(filename, true);
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
* @brief ����һ������Ȼ����Ƶ���Ļ�ϵ�λ��
* @param srcPos  Sprite�����texture�ļ���λ�ã�������NULL��ʹ��Sprite���õļ���λ��
* @param dstPos  Sprite���Ƶ���Ļ�ϵ�λ�ã�ֻ��Ҫλ�ò���Ҫ����
*/
void Sprite::draw(Graphics& graphics, SDL_Rect* srcPos, SDL_Rect* dstPos, 
	const SDL_RendererFlip flip) {
	graphics.render(texture_, srcPos? srcPos : &srcPos_, dstPos, flip);
}

bool operator==(const SDL_Rect & lhs, const SDL_Rect & rhs) {
	return (lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h);
}