#ifndef GAME_H_
#define GAME_H_
#include <SDL.h>
#include "Graphics.h"
#include "Sprite.h"
#include "Player.h"
#include "Map.h"

#include <iostream>
#include <memory>


class Game
{
public:
	Game();
	~Game();

	void eventloop();//�����ѭ��
	void update();//���ڸ�������
	void draw(Graphics& graphics);//���ڻ���
	void calculateFps(Uint32 elapsTime);
private:
	bool running = true;
	float avgFps = 0.0;
	Uint32 startTick = 0;
	Uint32 frameCount = 0;

	std::shared_ptr<Player> player_;
	std::shared_ptr<Map> caveMap_;
};



#endif // !GAME_H_