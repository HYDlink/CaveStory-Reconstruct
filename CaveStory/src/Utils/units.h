#ifndef UNITS_H_
#define UNITS_H_

#include <cmath>
#include <algorithm>
#include <SDL_types.h>
#include "Vector2d.h"

//��һ���뷨��ʵ�ֻ������챣�ֱ�������ֱ���, ò���е��鷳
enum HorizontalFacing : bool {
	FACING_LEFT,
	FACING_RIGHT
};
namespace units {
	typedef float Game;//����ʹ��float��ȡ����ȷ�ļ���
	typedef Uint16 Pixel;
	typedef Uint16 Tile;
	typedef Uint32 MS;
	typedef Uint32 FPS;
	typedef Uint8 Frame;//������֡��
	typedef float Degrees;

	typedef int8_t HP;//ԭ��Ϸ��ֵ, ����˺�-128

	typedef float Velocity;
	typedef float Accelration;//������һ���ŵ��Ƿ���ȷ�ϱ������ٶȻ��Ǽ��ٶ�
	typedef float AngularVelocity; // Degrees / MS

	const Pixel TileSize = 32;
	const Pixel HalfTile = 16;
	const Pixel BgTileSize = 128;

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