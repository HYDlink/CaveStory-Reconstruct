#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include <vector>
#include <fstream>

//ʹ��Tile�����TileMap
//ʹ���ļ�����tileMap
//ʹ�ñ���
//��������������������ƽ�б任����
class Map {
public:
	Map();
	~Map();

	void loadTile(Graphics& graphics, const std::string& filename, Uint8 rows, Uint8 cols);
	void loadMapData(const std::string& filename);
	void draw(Graphics& graphics);
private:
	std::shared_ptr<Tile> tile_;
	std::vector<std::vector<Uint16>> mapData_;//�洢tile��ص�λ��
};


#endif // !MAP_H_