#ifndef MAP_H_
#define MAP_H_

#include "Rectangle.h"
#include "Utils/units.h"
#include "GameObject.h"

#include <fstream>
#include <vector>
#include <SDL_render.h>

class Tile;
class FixedBackdrop;
//使用Tile类加载TileMap
//使用文件加载tileMap
//使用背景
//背景包含不动背景，和平行变换背景
//TODO 加载TileType数据, 前景和后景分离，各使用一个map类
using TileType = Uint8;
struct CollisionTile {
	units::Tile row, col;
	TileType type;
};

//TODO 分离前景Map和后景Map, 还有背景，洞窟的地图使用了三个文件存储一个地图
//TODO 分离Tile贴图数据和Map存储位置数据
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

	void load(const std::string& mapName);
	void loadTile(Graphics& graphics, const std::string& filename, units::Tile rows, units::Tile cols);
	//TODO 加载地图精灵对应的地形类型TileFlag
	void loadTileData(const std::string& filename, TileData& dataToStore);
	void loadMapData(const std::string& filename);
	void loadCache(const std::string& filename);

	units::Tile mapWidth() const;
	units::Tile mapHeight() const;
	Rectangle levelRect() const;
	void draw(Graphics& graphics) const;
protected:
	std::shared_ptr<Tile> tile_, bgTile_;
	MapData mapData_;//存储tile相关的位置
	SDL_Texture* mapCacheTexture_;
	units::Tile mapWidth_ = 0, mapHeight_ = 0;
	//普遍情况下应该不会有tileMap的行数或者列数超过uint8的吧，所以直接使用8位存储
};

class ForeGround : public Map, public GameObject {
public:
	ForeGround();
	std::vector<CollisionTile> getCollidingTiles(const Rectangle& r) const;
	void update(units::MS t) override {}
	void draw(Graphics& graphics) const override { Map::draw(graphics); }
};

//TODO
class CompleteMap: public GameObject {
public:
	CompleteMap(Graphics& graphics, std::string stageName, std::string backName);
private:
	std::string stageName_;
	std::string backName_;
	std::shared_ptr<ForeGround> fg_;
	std::shared_ptr<FixedBackdrop> fixedBd_;
	//foreGround, BackGround位于Children
};

#endif // !MAP_H_