#pragma once
#include "Sprite.h"
class Tile :
	public Sprite {
public:
	Tile(Graphics& graphics, const std::string& path, Uint8 tileRows, Uint8 tileCols);
	~Tile();
	void draw(Graphics& graphics, Uint8 row, Uint8 col, SDL_Rect* dstPos);
	const Uint8 getWidth() const { return tileWidth_; }
	const Uint8 getHeight() const { return tileHeight_; }
private:
	Uint8 tileWidth_, tileHeight_;//���������������͸�������Ҫ����ֻ���ڹ�������а�
	Uint8 tileRows_, tileCols_;
};

