#include "Tile.h"


Tile::Tile(Graphics& graphics, const std::string& path, units::Tile tileRows, units::Tile tileCols)
	:Sprite(graphics, path), tileCols_(tileCols), tileRows_(tileRows) {
	tileWidth_ = srcPos_.w / tileRows_;
	tileHeight_ = srcPos_.h / tileCols_;
}

Tile::~Tile() {
}

void Tile::draw(Graphics& graphics, units::Tile row, units::Tile col, SDL_Rect* dstPos) {
	SDL_Rect srcRect{ row * tileWidth_, col * tileHeight_, tileWidth_, tileHeight_ };
	Sprite::draw(graphics, &srcRect, dstPos);
}
