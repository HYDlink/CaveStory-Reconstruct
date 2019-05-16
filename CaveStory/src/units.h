#ifndef UNITS_H_
#define UNITS_H_

#include <math.h>
#include <SDL_types.h>
#include "Vector2d.h"

//有一个想法是实现画面拉伸保持比例增大分辨率, 貌似有点麻烦
//其实想把游戏所有的常量存到这里来, 不知道好不好
namespace units {
	typedef float Game;//可能使用float获取更精确的计算
	typedef Uint16 Pixel;
	typedef Uint16 Tile;
	typedef Uint32 MS;
	typedef Uint32 FPS;
	typedef Uint8 Frame;//动画的帧数
	typedef float Velocity;
	typedef float Accelration;//这样的一个优点是方便确认变量是速度还是加速度

	const Pixel TileSize = 32;
	const Pixel BgTileSize = 128;
	
	inline Pixel gameToPixel(Game v) {
		return Pixel(round(v));
	}
#if 0 //Uint到float直接隐式转换
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