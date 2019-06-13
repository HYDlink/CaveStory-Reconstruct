
//加载地图 
SDL_Rect srcRect{ 0, 0, units::TileSize, units::TileSize };
SDL_Rect dstRect{};

srcRect.x = units::tileToPixel(mapdata[i][j].first);
srcRect.y = units::tileToPixel(mapdata[i][j].second);
dstRect.x = units::tileToPixel(j);
dstRect.y = units::tileToPixel(i);

//使用函数闭包
dstRect.x = j * units::BgTileSize;
dstRect.y = i * units::BgTileSize;

