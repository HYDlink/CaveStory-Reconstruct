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
	player_ = make_shared<Player>(graphics, "res/MyChar.bmp");
	caveMap_ = make_shared<Map>();
	caveMap_->loadTile(graphics, "res/PrtCave.bmp", 16, 5);
	caveMap_->loadMapData("res/PrtCave.txt");

	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: running = false;
				break;
			}
		}

		draw(graphics);
		update();
	}
}

void Game::update()
{
	//calculateFps(1000);
	player_->update();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();

	graphics.draw();
	SDL_Rect position{ 100, 100, 0, 0 };
	player_->draw(graphics);
	caveMap_->draw(graphics);

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

