#ifndef MAP_H_
#define MAP_H_

#include "Backdrop.h"
#include "Rectangle.h"
#include "Tile.h"
#include "units.h"

#include <fstream>
#include <vector>

//ʹ��Tile�����TileMap
//ʹ���ļ�����tileMap
//ʹ�ñ���
//��������������������ƽ�б任����
//TODO ����TileType����
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
	//first�����У�second������
	using TileData = std::vector<std::vector<TileType>>;

	void loadTile(Graphics& graphics, const std::string& filename, units::Tile rows, units::Tile cols);
	//TODO ����tiledata������
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
	MapData mapData_, bgMapData_;//�洢tile��ص�λ��
	units::Tile mapWidth_ = 0, mapHeight_ = 0;
	//�ձ������Ӧ�ò�����tileMap������������������uint8�İɣ�����ֱ��ʹ��8λ�洢
};


#endif // !MAP_H_