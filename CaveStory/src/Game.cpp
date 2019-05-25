#include "Game.h"
#include "Enemys/Bat.h"
#include "Timer.h"

using namespace std;

//在移动或者调整窗口大小的情况下，sdl会停止工作，这样会造成一个很大的延迟时间
//这样的情况下会产生一些奇怪的毛病，比如我这里是
//解决方法是使用一个最大延迟时间clamp稳定住延迟时间
const units::MS maxDeltaTime = 100;

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		cerr << "SDL_Init Error: " << SDL_GetError() << endl;
	eventloop();
}


Game::~Game()
{
	SDL_Quit();
}

void Game::eventloop()
{
	Graphics graphics;
	startTick = SDL_GetTicks();
	caveMap_ = make_shared<Map>();
	caveMap_->loadTile(graphics, "res/PrtCave.bmp", 16, 5);
	caveMap_->loadFgMapData("res/PrtCave.txt");
	caveMap_->loadBd(graphics, "res/bkBlue.bmp");
	numberSprite_ = make_shared<NumberSprite>(graphics, "res/TextBox.bmp");
	player_ = make_shared<Player>(graphics, caveMap_, "res/MyChar.bmp", 240, 240);
	bat_ = make_shared<Bat>(graphics, *player_, "res/NpcCemet.bmp", 
		Position2D(units::tileToPixel(3), units::tileToPixel(5)));

	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: running = false;
				break;
			}
			player_->handleEvent(e);
		}

		draw(graphics);
		update();
	}
}

void Game::update()
{
	units::MS deltaTime = SDL_GetTicks() - startTick;
	deltaTime = std::min(deltaTime, maxDeltaTime);
	calculateFps(1000);

	Timer::updateAll(deltaTime);
	player_->update(deltaTime);
	bat_->update(deltaTime);
	startTick = SDL_GetTicks();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	graphics.draw();
	caveMap_->drawBd(graphics);

	SDL_Rect position{ 100, 100, 0, 0 };
	player_->draw(graphics, *numberSprite_);
	bat_->draw(graphics, *numberSprite_);

	caveMap_->drawFg(graphics);

	graphics.present();
}

//elapsTime代表重新计算FPS的间隔时间
void Game::calculateFps(units::MS elapsTime)
{
	//TODO
	//计算fps
	++frameCount;//莫名奇妙，这个framecount加的次数很多
	units::MS nowTick = SDL_GetTicks();
	if (nowTick - startTick > elapsTime) {
		const float tmp = (float)(nowTick - startTick) / 1000;
		cout << frameCount<< " "; 
		avgFps = frameCount / tmp;
		frameCount = 0;
		startTick = nowTick;
		cout << tmp << " "<< avgFps << endl;
	}
}

