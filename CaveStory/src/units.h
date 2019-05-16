#ifndef UNITS_H_
#define UNITS_H_

#include <math.h>
#include <SDL_types.h>
#include "Vector2d.h"

//��һ���뷨��ʵ�ֻ������챣�ֱ�������ֱ���, ò���е��鷳
//��ʵ�����Ϸ���еĳ����浽������, ��֪���ò���
namespace units {
	typedef float Game;//����ʹ��float��ȡ����ȷ�ļ���
	typedef Uint16 Pixel;
	typedef Uint16 Tile;
	typedef Uint32 MS;
	typedef Uint32 FPS;
	typedef Uint8 Frame;//������֡��
	typedef float Velocity;
	typedef float Accelration;//������һ���ŵ��Ƿ���ȷ�ϱ������ٶȻ��Ǽ��ٶ�

	const Pixel TileSize = 32;
	const Pixel BgTileSize = 128;
	
	inline Pixel gameToPixel(Game v) {
		return Pixel(round(v));
	}
#if 0 //Uint��floatֱ����ʽת��
	inline Game pixelToGame(Pixel v) {
		return Game(v);
	}
#endif

	inline Tile gameToTile(Game game) {
		return Tile(game / TileSize);
	}

	inline Tile pixelToTile(Pixel pixel) {
		return Tile(pixel / TileSize);
	}

	inline Pixel tileToPixel(Tile tile) {
		return tile * TileSize;
	}

	inline Game tileToGame(Tile tile) {
		return tileToPixel(tile);
	}
}
typedef Vector2D<units::Game> Position2D;
typedef Vector2D<units::Game> Dimensions2D;

#endif // !UNITS_H_