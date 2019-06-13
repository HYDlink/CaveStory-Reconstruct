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
//ʹ��Tile�����TileMap
//ʹ���ļ�����tileMap
//ʹ�ñ���
//��������������������ƽ�б任����
//TODO ����TileType����, ǰ���ͺ󾰷��룬��ʹ��һ��map��
using TileType = Uint8;
struct CollisionTile {
	units::Tile row, col;
	TileType type;
};

//TODO ����ǰ��Map�ͺ�Map, ���б��������ߵĵ�ͼʹ���������ļ��洢һ����ͼ
//TODO ����Tile��ͼ���ݺ�Map�洢λ������
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
	//first�����У�second������
	using TileData = std::vector<std::vector<TileType>>;

	void load(const std::string& mapName);
	void loadTile(Graphics& graphics, const std::string& filename, units::Tile rows, units::Tile cols);
	//TODO ���ص�ͼ�����Ӧ�ĵ�������TileFlag
	void loadTileData(const std::string& filename, TileData& dataToStore);
	void loadMapData(const std::string& filename);
	void loadCache(const std::string& filename);

	units::Tile mapWidth() const;
	units::Tile mapHeight() const;
	Rectangle levelRect() const;
	void draw(Graphics& graphics) const;
protected:
	std::shared_ptr<Tile> tile_, bgTile_;
	MapData mapData_;//�洢tile��ص�λ��
	SDL_Texture* mapCacheTexture_;
	units::Tile mapWidth_ = 0, mapHeight_ = 0;
	//�ձ������Ӧ�ò�����tileMap������������������uint8�İɣ�����ֱ��ʹ��8λ�洢
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
	//foreGround, BackGroundλ��Children
};

#endif // !MAP_H_