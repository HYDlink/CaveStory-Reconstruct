#include "Backdrop.h"
#include "units.h"

FixedBackdrop::FixedBackdrop(Graphics& graphics, const std::string& path) {
	texture_ = graphics.loadFromFile(path);
}

void FixedBackdrop::draw(Graphics& graphics) const {
	SDL_Rect dstRect = SDL_Rect();
	graphics.render(texture_, NULL, NULL);
	for(units::Tile i = 0; i < screenHeight; i += units::BgTileSize)
		for (units::Tile j = 0; j < screenWidth; j += units::BgTileSize) {
			dstRect.x = j;
			dstRect.y = i;
			graphics.render(texture_, NULL, &dstRect);
		}
}
