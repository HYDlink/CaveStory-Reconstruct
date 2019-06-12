#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include <iostream>
#include <memory>
#include "Utils/units.h"

class Scene;
class Graphics;
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
	
	std::shared_ptr<Scene> scene_;
	// std::vector<std::shared_ptr<Scene>> scenes_;
};



#endif // !GAME_H_