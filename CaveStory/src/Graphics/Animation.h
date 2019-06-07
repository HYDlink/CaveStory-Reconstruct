#pragma once
#include "Sprite.h"
#include "../Utils/units.h"
#include <vector>

//TODO
//建立Animator类控制Animation，并使用状态机
//洞窟物语所有精灵图默认单位长宽是32，也就是说用一堆SDL_Rect构造可以去改掉, 省去很多麻烦, 到时候看看吧
class Animation :
	public Sprite {
public:
	Animation(Graphics& graphics, const std::string& filename, bool black_is_transparent = true);
	Animation(Graphics& graphics, const std::string& filename, 
		const std::vector<SDL_Rect>& frames, bool black_is_transparent = true);
	Animation(Graphics& graphics, const std::string& filename,
		std::vector<SDL_Rect>&& frames);
	~Animation();

	void setFrames(const std::vector<SDL_Rect>& frames) 
	{ frames_ = frames; totalFrames_ = frames.size(); }
	units::Frame getFrames() const { return totalFrames_; }
	units::Frame getCurFrame() const { return currentFrame_; }

	// bg和ed都设置为0或者非法值开始默认所有的动画
	void start_Animation(units::Frame bg, units::Frame ed, 
		units::MS framesPerFrame, bool loop = false, const SDL_RendererFlip flip = SDL_FLIP_NONE);
	void flip(const SDL_RendererFlip flip) { flip_ = flip; }
	void update();
	void draw(Graphics& graphics, SDL_Rect* dstPos) const;
private:
	std::vector<SDL_Rect> frames_;
	bool loop_ = false;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;

	units::Frame totalFrames_;
	units::Frame currentFrame_;
	units::Frame startFrame_;
	units::Frame endFrame_;

	units::Frame currentTime_;
	units::MS elapsTime_ = 4;//每一动画帧中间间隔多少时间帧
};

