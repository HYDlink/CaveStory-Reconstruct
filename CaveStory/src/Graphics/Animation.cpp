#include <iostream>
#include "Animation.h"
using namespace std;

Animation::Animation(Graphics& graphics, const std::string& filename, 
	TransparentColor color) :
	Sprite(graphics, filename, color), currentFrame_(0), startFrame_(0), endFrame_(0),
	totalFrames_(0), currentTime_(0) {
}

Animation::Animation(Graphics& graphics, const std::string& filename,
	const std::vector<SDL_Rect>& frames, TransparentColor color):
	Sprite(graphics, filename, color), frames_(frames),
    currentFrame_(0), startFrame_(0), endFrame_(0),
	totalFrames_(frames.size()), currentTime_(0){}

Animation::Animation(Graphics& graphics, const std::string& filename, 
	std::vector<SDL_Rect>&& frames): Sprite(graphics, filename), frames_(frames),
	currentFrame_(0), startFrame_(0), endFrame_(0),
	totalFrames_(frames.size()), currentTime_(0) {}

Animation::~Animation() {
}


void Animation::start_Animation(units::Frame bg, units::Frame ed,
	                            units::MS framesPerFrame, bool loop,
	                            const SDL_RendererFlip flip) {
	elapsTime_ = framesPerFrame;
	loop_ = loop;
	flip_ = flip;
	// bg和ed都设置为0或者非法值开始默认所有的动画
	if (bg > ed || bg > totalFrames_ || ed > totalFrames_) {
		bg = 0;
		ed = totalFrames_ - 1;
	}
	if (bg == startFrame_ && ed == endFrame_)
		//就是重复调用了, 这里elapsTime, 可能以后会用到慢速的功能, 所以需要保持现在的帧位置不变
		return;
	startFrame_ = bg;
	endFrame_ = ed;
	currentTime_ = 0;
}

//loop为false情况下，动画结束后保持在endFrame_
void Animation::update() {
	//在没有start_Aniamtion()的情况下, 默认startFrame_和endFrame_为0
	//如果继续下去, 会触发stoped_=true;
	if (startFrame_ == endFrame_) {
		currentFrame_ = startFrame_;
		return;
	}

	currentTime_++;
	currentFrame_ = startFrame_ + currentTime_ / elapsTime_;
	if (currentFrame_ > endFrame_) {
		if (loop_) {
			currentFrame_ = startFrame_;//循环
			currentTime_ = 0;
		}
		else {
			currentFrame_ = /*defaultFrame_*/endFrame_;
			stoped_ = true;
			return;
		}
	}
}

void Animation::draw(Graphics& graphics, SDL_Rect* dstPos) const {
	Sprite::draw(graphics, &frames_[currentFrame_], dstPos, false, flip_);
}
