#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include "Backdrop.h"
#include <vector>
#include <fstream>

//使用Tile类加载TileMap
//使用文件加载tileMap
//使用背景
//背景包含不动背景，和平行变换背景
class Map {
	using MapData = std::vector<std::vector<std::pair<Uint8, Uint8>>>;
public:
	Map();
	~Map();

	void loadTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols);
	void loadMapData(const std::string& filename, MapData& dataToStore);
	void loadFgMapData(const std::string& filename);
	void loadBgTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols);
	void loadBgMapData(const std::string& filename);
	void loadBd(Graphics& graphics, const std::string& filename);

	void drawBd(Graphics& graphics);
	void drawFg(Graphics& graphics);
private:
	std::shared_ptr<Tile> tile_, bgTile_;
	std::shared_ptr<FixedBackdrop> fixedBd;
	MapData mapData_, bgMapData_;//存储tile相关的位置
	//普遍情况下应该不会有tileMap的行数或者列数超过Uint8的吧，所以直接使用8位存储
};


#endif // !MAP_H_