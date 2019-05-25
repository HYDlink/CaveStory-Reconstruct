#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include "Graphics.h"
#include "HUD/NumberSprite.h"
#include "Sprite.h"
#include "Player.h"
#include "Map.h"
#include "units.h"

#include <iostream>
#include <memory>

class Bat;
class Game
{
public:
	Game();
	~Game();

	void eventloop();//整体的循环
	void update();//用于更新数据
	void draw(Graphics& graphics);//用于绘制
	void calculateFps(units::MS elapsTime);
private:
	bool running = true;
	units::FPS avgFps = 0.0;
	units::MS startTick = 0;
	units::FPS frameCount = 0;

	std::shared_ptr<Player> player_;
	std::shared_ptr<Bat> bat_;
	std::shared_ptr<Map> caveMap_;
	std::shared_ptr<NumberSprite> numberSprite_;
};



#endif // !GAME_H_