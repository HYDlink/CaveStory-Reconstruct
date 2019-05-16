#ifndef MAP_H_
#define MAP_H_

#include "Backdrop.h"
#include "Rectangle.h"
#include "Tile.h"
#include "units.h"

#include <fstream>
#include <vector>

//使用Tile类加载TileMap
//使用文件加载tileMap
//使用背景
//背景包含不动背景，和平行变换背景
//TODO 加载TileType数据
using TileType = Uint8;
struct CollisionTile {
	units::Tile row, col;
	TileType type;
};

class Map {
public:
	Map();
	~Map();

	enum TileFlag: Uint8 {
		EMPTY = 0b0000,
		WALL = 0b0001,
		SLOPE = 0b0010,

		LEFT_SLOPE = 0b0100,
		RIGHT_SLOPE = 0b0000,

		TOP_SLOPE = 0b1000,
		BOTTOM_SLOPE = 0,

		TALL_SLOPE = 0b10000,
		SHORT_SLOPE = 0
	};
	//TileType getTileType(TileFlag);
	using MapData = std::vector<std::vector<std::pair<units::Tile, units::Tile>>>;
	//first代表行，second代表列
	using TileData = std::vector<std::vector<TileType>>;

	void loadTile(Graphics& graphics, const std::string& filename, units::Tile rows, units::Tile cols);
	//TODO 保存tiledata的类型
	void loadTileData(const std::string& filename, TileData& dataToStore);
	void loadMapData(const std::string& filename, MapData& dataToStore);
	void loadFgMapData(const std::string& filename);
	void loadBgTile(Graphics& graphics, const std::string& filename, units::Tile rows, units::Tile cols);
	void loadBgMapData(const std::string& filename);
	void loadBd(Graphics& graphics, const std::string& filename);

	std::vector<CollisionTile> getCollidingTiles(const Rectangle& r) const;

	void drawBd(Graphics& graphics);
	void drawFg(Graphics& graphics);
private:
	std::shared_ptr<Tile> tile_, bgTile_;
	std::shared_ptr<FixedBackdrop> fixedBd;
	MapData mapData_, bgMapData_;//存储tile相关的位置
	units::Tile mapWidth_ = 0, mapHeight_ = 0;
	//普遍情况下应该不会有tileMap的行数或者列数超过uint8的吧，所以直接使用8位存储
};


#endif // !MAP_H_