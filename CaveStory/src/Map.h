#ifndef MAP_H_
#define MAP_H_

#include "Tile.h"
#include "Backdrop.h"
#include <vector>
#include <fstream>

//ʹ��Tile�����TileMap
//ʹ���ļ�����tileMap
//ʹ�ñ���
//��������������������ƽ�б任����
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
	MapData mapData_, bgMapData_;//�洢tile��ص�λ��
	//�ձ������Ӧ�ò�����tileMap������������������Uint8�İɣ�����ֱ��ʹ��8λ�洢
};


#endif // !MAP_H_