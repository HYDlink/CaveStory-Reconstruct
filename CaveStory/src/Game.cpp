#include "Game.h"

using namespace std;

//���ƶ����ߵ������ڴ�С������£�sdl��ֹͣ���������������һ���ܴ���ӳ�ʱ��
//����������»����һЩ��ֵ�ë����������������
//���������ʹ��һ������ӳ�ʱ��clamp�ȶ�ס�ӳ�ʱ��
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
	calculateFps(1000);
	player_->update(std::min((SDL_GetTicks() - startTick), maxDeltaTime));
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

//elapsTime�������¼���FPS�ļ��ʱ��
void Game::calculateFps(units::MS elapsTime)
{
	//TODO
	//����fps
	++frameCount;//Ī��������framecount�ӵĴ����ܶ�
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

