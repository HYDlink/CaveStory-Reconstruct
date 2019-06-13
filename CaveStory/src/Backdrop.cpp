#include "Backdrop.h"
#include "Utils/units.h"

FixedBackdrop::FixedBackdrop(Graphics& graphics, const std::string& path):
    FixedBackdrop(graphics, path, 0, 0){}

FixedBackdrop::FixedBackdrop(Graphics& graphics, const std::string& path,
	units::Tile width, units::Tile height): width_(width), height_(height), filename_(path), 
    GameObject(LAYER::BACKDROP) {
	if (width_ > 0 && height_ > 0)
		texture_ = graphics.loadBgTexture(path, width_, height_);
}

/** \brief ���ñ�����С��ͬʱ������ͼ���棬�����ҪGraphics
 * 
 */
void FixedBackdrop::setSize(Graphics& graphics, units::Tile width, units::Tile height) {
	width_ = width;
	height_ = height;
	texture_ = graphics.loadBgTexture(filename_, width_, height_);
}

void FixedBackdrop::draw(Graphics& graphics) const {
	SDL_Rect dstRect = SDL_Rect();
	graphics.render(texture_, NULL, NULL);
#if 0
	for(units::Tile i = 0; i < height_; i++)
		for (units::Tile j = 0; j < width_; j++) {
			dstRect.x =j * units::BgTileSize;
			dstRect.y = i * units::BgTileSize;
			graphics.render(texture_, NULL, &dstRect);
		}
#else
	graphics.render(texture_, NULL, &dstRect);
#endif
}
