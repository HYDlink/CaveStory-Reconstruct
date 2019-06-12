#include "Map.h"
#include "Backdrop.h"
#include "Tile.h"
#include "GameObject.h"
#include <sstream>

using namespace std;

Map::Map() {
}


Map::~Map() {
}

void Map::loadTile(Graphics& graphics, const std::string& filename, units::Tile rows, units::Tile cols) {
	tile_.reset(new Tile(graphics, filename, rows, cols));
}

void Map::loadTileData(const std::string& filename, TileData& dataToStore) {
	dataToStore.clear();
	ifstream mapFile(filename);
	units::Tile width = tile_->getWidth(), height = tile_->getHeight();
	TileType tmpData;
	for (units::Tile i = 0; i < height; ++i) {
		vector<TileType> tmpRow;
		for (units::Tile j = 0; j < width; ++j) {
			mapFile >> tmpData;
			tmpRow.push_back(tmpData);
		}
		dataToStore.push_back(tmpRow);
	}
}

//TODO 可能使用二进制读取文件，想做一个地图编辑器
void Map::loadMapData(const std::string& filename) {
	mapData_.clear();
	ifstream mapFile(filename);
	units::Tile tmpData;
	string tmpStr;
	while (getline(mapFile, tmpStr)) {
		vector<pair<units::Tile, units::Tile>> tmpRow;
		stringstream stream(tmpStr);
		while(stream >> tmpData)
			tmpRow.push_back(make_pair<units::Tile, units::Tile>(tmpData & 0x00ff, tmpData & 0xff00));
		mapData_.push_back(tmpRow);
	}
	mapHeight_ = mapData_.size();
	mapWidth_ = mapData_[0].size();
}

units::Tile Map::mapWidth() const { return mapWidth_; }

units::Tile Map::mapHeight() const { return mapHeight_; }

Rectangle Map::levelRect() const {
	return Rectangle(0, 0, units::tileToGame(mapWidth_), units::tileToGame(mapHeight_));
}

void Map::draw(Graphics& graphics) const {
	units::Tile cols = mapData_.size(), rows = mapData_[0].size();
	units::Tile width = tile_->getWidth(), height = tile_->getHeight();
	for (units::Tile i = 0; i < cols; ++i) {
		for (units::Tile j = 0; j < rows; ++j) {
			SDL_Rect dstPos{ j * width, i * height, 0, 0 };
			tile_->draw(graphics, mapData_[i][j].first, mapData_[i][j].second, &dstPos);
		}
	}
}

ForeGround::ForeGround() : GameObject(LAYER::FOREGROUND) {}

//TODO 检测Tile类型而不是单纯返回mapData是否在特定位置什么的
std::vector<CollisionTile> ForeGround::getCollidingTiles(const Rectangle& r) const {
	std::vector<CollisionTile> result;
	units::Tile left = units::gameToTile(r.left());
	units::Tile right = units::gameToTile(r.right());
	units::Tile bottom = units::gameToTile(r.bottom());
	units::Tile top = units::gameToTile(r.top());
	for (units::Tile i = top; i <= bottom && i < mapHeight_; ++i) {
		for (units::Tile j = left; j <= right && j < mapWidth_; ++j) {
			result.push_back(CollisionTile{ j, i, mapData_[i][j].first/*TODO*/ ? WALL : EMPTY });
		}
	}
	return result;
}
