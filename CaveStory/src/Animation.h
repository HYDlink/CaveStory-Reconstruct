#pragma once
#include "Sprite.h"
#include "units.h"
#include <vector>

//TODO
//建立Animator类控制Animation，并使用状态机
//洞窟物语所有精灵图默认单位长宽是32，也就是说用一堆SDL_Rect构造可以去改掉, 省去很多麻烦, 到时候看看吧
class Animation :
	public Sprite {
public:
	Animation(Graphics& graphics, const std::string& filename, 
		const std::vector<SDL_Rect>& frames);
	~Animation();

	units::Frame getFrames() { return totalFrames_; }
	void start_Animation(units::Frame bg, units::Frame ed, units::MS framesPerFrame, bool loop = false);
	void update();
	void draw(Graphics& graphics, SDL_Rect* dstPos);
private:
	std::vector<SDL_Rect> frames_;
	bool loop_ = false;

	units::Frame totalFrames_;
	units::Frame currentFrame_;
	units::Frame startFrame_;
	units::Frame endFrame_;

	units::Frame currentTime_;
	units::MS elapsTime_ = 4;//每一动画帧中间间隔多少时间帧
};

