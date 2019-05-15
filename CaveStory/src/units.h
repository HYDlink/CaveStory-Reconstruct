#ifndef UNITS_H_
#define UNITS_H_

#include <math.h>
#include <SDL_types.h>
#include "Vector2d.h"

namespace units {
	typedef int Game;
	typedef Uint16 Tile;
	const Uint16 TileSize = 32;
	const Uint16 BgTileSize = 128;

}
typedef Vector2D<units::Game> Position2D;
typedef Vector2D<units::Game> Dimensions2D;

#endif // !UNITS_H_