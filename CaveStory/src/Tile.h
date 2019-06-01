#pragma once
#include "Sprite.h"
#include "Utils/units.h"

class Tile :
	public Sprite {
public:
	Tile(Graphics& graphics, const std::string& path, units::Tile tileRows, units::Tile tileCols);
	~Tile();
	void draw(Graphics& graphics, units::Tile row, units::Tile col, SDL_Rect* dstPos);
	const units::Tile getWidth() const { return tileWidth_; }
	const units::Tile getHeight() const { return tileHeight_; }
private:
	units::Tile tileWidth_, tileHeight_;//���������������͸�������Ҫ����ֻ���ڹ�������а�
	units::Tile tileRows_, tileCols_;
};

