#include "Backdrop.h"

namespace {
	const Uint8 BackgroundSize = 128;
}
FixedBackdrop::FixedBackdrop(Graphics& graphics, const std::string& path) {
	texture_ = graphics.loadFromFile(path);
}

void FixedBackdrop::draw(Graphics& graphics) const {
	SDL_Rect dstRect = SDL_Rect();
	graphics.render(texture_, NULL, NULL);
	for(Uint16 i = 0; i < screenHeight; i += BackgroundSize)
		for (Uint16 j = 0; j < screenWidth; j += BackgroundSize) {
			dstRect.x = j;
			dstRect.y = i;
			graphics.render(texture_, NULL, &dstRect);
		}
}
