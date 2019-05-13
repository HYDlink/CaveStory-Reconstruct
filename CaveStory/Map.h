#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include <vector>
#include <fstream>

//使用Tile类加载TileMap
//使用文件加载tileMap
//使用背景
//背景包含不动背景，和平行变换背景
class Map {
public:
	Map();
	~Map();

	void loadTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols);
	void loadMapData(const std::string& filename);
	void draw(Graphics& graphics);
private:
	std::shared_ptr<Tile> tile_;
	std::vector<std::vector<Uint16>> mapData_;//存储tile相关的位置
};


#endif // !MAP_H_