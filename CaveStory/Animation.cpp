#include "Animation.h"

#include <iostream>
using namespace std;

Animation::Animation(Graphics& graphics, const std::string& filename, 
	const std::vector<SDL_Rect>& frames):Sprite(graphics, filename), frames_(frames),
    currentFrame_(0), startFrame_(0), endFrame_(0), totalFrames_(frames.size()), currentTime_(0){
	
}

Animation::~Animation() {
}


void Animation::start_Animation(size_t bg, size_t ed, Uint16 framesPerFrame, bool loop) {
	elapsTime_ = framesPerFrame;
	loop_ = loop;
	if (bg == startFrame_ && ed == endFrame_)
		//就是重复调用了, 这里elapsTime, 可能以后会用到慢速的功能, 所以需要保持现在的帧位置不变
		return;
	if (bg > totalFrames_ || ed > totalFrames_) {
		cerr << "Out of Range" << endl;
		return;
	}
	startFrame_ = bg;
	endFrame_ = ed;
	currentTime_ = 0;
}

void Animation::update() {
	currentTime_++;
	currentFrame_ = startFrame_ + currentTime_ / elapsTime_;
	if (currentFrame_ > endFrame_){
		currentFrame_ = startFrame_;//循环
		currentTime_ = 0;
		//这里有点检测问题，如果currentFrame_过了endFrame_的话, 那么在最后的动画还进行了一个时间帧...
	}
}

void Animation::draw(Graphics& graphics, SDL_Rect* dstPos) {
	Sprite::draw(graphics, &frames_[currentFrame_], dstPos);
}
