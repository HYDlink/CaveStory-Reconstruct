#include "Game.h"

using namespace std;

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
	player_ = make_shared<Player>(graphics, caveMap_, "res/MyChar.bmp", 240, 240);

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
	//calculateFps(1000);
	player_->update(SDL_GetTicks() - startTick);
	startTick = SDL_GetTicks();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	graphics.draw();
	caveMap_->drawBd(graphics);
	SDL_Rect position{ 100, 100, 0, 0 };
	player_->draw(graphics);
	caveMap_->drawFg(graphics);

	graphics.present();
}

void Game::calculateFps(Uint32 elapsTime)
{
	//计算fps
	++frameCount;//莫名奇妙，这个framecount加的次数很多
	Uint32 nowTick = SDL_GetTicks();
	if (nowTick - startTick > elapsTime) {
		const float tmp = (float)(nowTick - startTick) / 1000;
		cout << frameCount<< " "; 
		avgFps = frameCount / tmp;
		frameCount = 0;
		startTick = nowTick;
		cout << tmp << " "<< avgFps << endl;
	}
}

