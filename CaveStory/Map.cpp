#include "Map.h"



Map::Map() {
}


Map::~Map() {
}

void Map::loadTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols) {
	tile_.reset(new Tile(graphics, filename, rows, cols));
}

void Map::loadMapData(const std::string& filename) {

}

void Map::draw(Graphics& graphics) {
	size_t cols = mapData_.size(), rows = mapData_[0].size();
	Uint8 width = tile_->getWidth, height = tile_->getHeight;
	for (size_t i = 0; i < cols; ++i) {
		for (size_t j = 0; j < rows; ++j) {
			SDL_Rect dstPos{ j * width, i * height, 0, 0 };
			tile_->draw(graphics, mapData_[i][j], mapData_[i][j])
		}
	}
}
