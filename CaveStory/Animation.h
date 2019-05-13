#pragma once
#include "Sprite.h"
#include <vector>

//TODO
//����Animator�����Animation����ʹ��״̬��
class Animation :
	public Sprite {
public:
	Animation(Graphics& graphics, const std::string& filename, 
		const std::vector<SDL_Rect>& frames);
	~Animation();

	void start_Animation(size_t bg, size_t ed, Uint16 framesPerFrame, bool loop = false);
	void update();
	void draw(Graphics& graphics, SDL_Rect* dstPos);
private:
	std::vector<SDL_Rect> frames_;
	bool loop_ = false;

	Uint16 totalFrames_;
	Uint16 currentFrame_;
	Uint16 startFrame_;
	Uint16 endFrame_;

	Uint16 currentTime_;
	Uint16 elapsTime_ = 4;//ÿһ����֡�м�������ʱ��֡
};

