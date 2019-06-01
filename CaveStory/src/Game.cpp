#include "Game.h"
#include "Enemys/Bat.h"
#include "Timer.h"
#include "Scenes/Cave0.h"
#include "Scenes/ParticleTest.h"
#include "CSCamera.h"

#define CSCAMERA

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

void Game::eventloop() {
	Graphics graphics;
	scene_ = make_shared<ParticleTest>();
	//scene_.reset(new Cave0);
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: running = false;
				break;
			}
			scene_->handleEvent(&e);
		}
		update();
		graphics.clear();
		scene_->draw(graphics);
		graphics.present();
	}
}

void Game::update()
{
	units::MS deltaTime = SDL_GetTicks() - startTick;
	deltaTime = std::min(deltaTime, maxDeltaTime);
	calculateFps(1000);
	Timer::updateAll(deltaTime);
	scene_->update(deltaTime);
	startTick = SDL_GetTicks();
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
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

