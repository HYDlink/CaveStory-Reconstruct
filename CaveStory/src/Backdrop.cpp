#include "Backdrop.h"
#include "units.h"

FixedBackdrop::FixedBackdrop(Graphics& graphics, const std::string& path):
    FixedBackdrop(graphics, path, 0, 0){}

FixedBackdrop::FixedBackdrop(Graphics& graphics, const std::string& path,
	units::Tile width, units::Tile height): width_(width), height_(height) {
	texture_ = graphics.loadFromFile(path);
}

void FixedBackdrop::setSize(units::Tile width, units::Tile height) {
	width_ = width;
	height_ = height;
}

void FixedBackdrop::draw(Graphics& graphics) const {
	SDL_Rect dstRect = SDL_Rect();
	graphics.render(texture_, NULL, NULL);
	for(units::Tile i = 0; i < height_; i++)
		for (units::Tile j = 0; j < width_; j++) {
			dstRect.x =j * units::BgTileSize;
			dstRect.y = i * units::BgTileSize;
			graphics.render(texture_, NULL, &dstRect);
		}
}
