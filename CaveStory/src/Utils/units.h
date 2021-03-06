#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>
#include <algorithm>
#include <SDL_types.h>
#include "Vector2d.h"

//TODO !! https://en.cppreference.com/w/cpp/language/user_literal
//有一个想法是实现画面拉伸保持比例增大分辨率, 貌似有点麻烦
namespace units {
	typedef float Game;//可能使用float获取更精确的计算
	typedef Uint16 Pixel;
	typedef Uint16 Tile;
	typedef Uint32 MS;
	typedef Uint32 FPS;
	typedef Uint8 Frame;//动画的帧数
	typedef Uint8 GunLevel;
	typedef Uint8 GunExperience;
	typedef float Degrees;

	typedef int8_t HP;//原游戏数值, 最大伤害-128

	typedef float Velocity;
	typedef float Acceleration;//这样的一个优点是方便确认变量是速度还是加速度
	typedef float AngularVelocity; // Degrees / MS

	constexpr const Pixel TileSize = 32;
	constexpr const Pixel HalfTile = 16;
	constexpr const Pixel BgTileSize = 128;
	constexpr const Pixel ScreenWidth = 640;
	constexpr const Pixel ScreenHeight = 480;
	constexpr const Tile ScreenTileWidth = ScreenWidth / units::TileSize;
	constexpr const Tile ScreenTileHeight = ScreenHeight / units::TileSize;
	constexpr const MS animationDelta = 4;
	constexpr const Uint8 MaxGunLevel = 32;

	enum ALIGN {
		LEFT_ALIGNED,
		CENTER_ALIGNED,
		RIGHT_ALIGNED
	};
	inline double degreesToRadians(Degrees degrees) {
		return degrees * M_PI / 180.0f;
	}

	inline Game cos(Degrees degrees) {
		return static_cast<Game>(std::cos(degreesToRadians(degrees)));
	}

	inline Game sin(Degrees degrees) {
		return static_cast<Game>(std::sin(degreesToRadians(degrees)));
	}

	inline Pixel gameToPixel(Game v) {
		return Pixel(round(v));
	}
	inline Game pixelToGame(Pixel v) {
		return static_cast<Game>(v);
	}

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

	inline Pixel getAlinedResult(Pixel dst, Pixel width, ALIGN align) {
		switch (align) {
		case units::LEFT_ALIGNED: return dst;
			break;
		case units::CENTER_ALIGNED: return dst - width / 2;
			break;
		case units::RIGHT_ALIGNED: return dst - width;
			break;
		}
	}
}
using Position2D = Vector2D<units::Game>;
using Dimensions2D = Vector2D<units::Game>;

#endif // !UNITS_H_