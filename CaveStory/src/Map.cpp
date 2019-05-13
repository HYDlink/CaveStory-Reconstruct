#include "Map.h"

using namespace std;

Map::Map() {
}


Map::~Map() {
}

void Map::loadTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols) {
	tile_.reset(new Tile(graphics, filename, rows, cols));
}

void Map::loadMapData(const std::string& filename, MapData& dataToStore) {
	dataToStore.clear();
	ifstream mapFile(filename);
	size_t width, height;
	//TODO 打开文件出错的处理
	mapFile >> width >> height;
	Uint16 tmpData;
	for (size_t i = 0; i < height; ++i) {
		vector<pair<Uint8, Uint8>> tmpRow;
		for (size_t j = 0; j < width; ++j) {
			mapFile >> tmpData;
			tmpRow.push_back(make_pair<Uint8, Uint8>(tmpData & 0x00ff, tmpData & 0xff00));
		}
		dataToStore.push_back(tmpRow);
	}
}

void Map::loadFgMapData(const std::string& filename) {
	loadMapData(filename, mapData_);
}

void Map::loadBgTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols) {
	tile_.reset(new Tile(graphics, filename, rows, cols));
}

void Map::loadBgMapData(const std::string& filename) {
	loadMapData(filename, bgMapData_);
}

void Map::loadBd(Graphics& graphics, const std::string& filename) {
	fixedBd.reset(new FixedBackdrop(graphics, filename));
}

void Map::drawBd(Graphics& graphics) {
	fixedBd->draw(graphics);
}

void Map::drawFg(Graphics& graphics) {
	size_t cols = mapData_.size(), rows = mapData_[0].size();
	Uint8 width = tile_->getWidth(), height = tile_->getHeight();
	for (size_t i = 0; i < cols; ++i) {
		for (size_t j = 0; j < rows; ++j) {
			SDL_Rect dstPos{ j * width, i * height, 0, 0 };
			tile_->draw(graphics, mapData_[i][j].first, mapData_[i][j].second, &dstPos);
		}
	}
}
