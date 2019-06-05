#include <iostream>
#include "Animation.h"
using namespace std;

Animation::Animation(Graphics& graphics, const std::string& filename) :
	Sprite(graphics, filename), currentFrame_(0), startFrame_(0), endFrame_(0),
	totalFrames_(0), currentTime_(0) {
}

Animation::Animation(Graphics& graphics, const std::string& filename,
	const std::vector<SDL_Rect>& frames):Sprite(graphics, filename), frames_(frames),
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
	if (bg == startFrame_ && ed == endFrame_)
		//�����ظ�������, ����elapsTime, �����Ժ���õ����ٵĹ���, ������Ҫ�������ڵ�֡λ�ò���
		return;
	// bg��ed������Ϊ0���߷Ƿ�ֵ��ʼĬ�����еĶ���
	if (bg >= ed || bg > totalFrames_ || ed > totalFrames_) {
		bg = 0;
		ed = totalFrames_;
	}
	startFrame_ = bg;
	endFrame_ = ed;
	currentTime_ = 0;
}

//loopΪfalse����£����������󱣳���endFrame_
void Animation::update() {
	currentTime_++;
	currentFrame_ = startFrame_ + currentTime_ / elapsTime_;
	if (currentFrame_ > endFrame_) {
		if (loop_) {
			currentFrame_ = startFrame_;//ѭ��
			currentTime_ = 0;
		}
		else {
			currentFrame_ = /*defaultFrame_*/endFrame_;
			return;
		}
	}
}

void Animation::draw(Graphics& graphics, SDL_Rect* dstPos) const {
	Sprite::draw(graphics, &frames_[currentFrame_], dstPos, false, flip_);
}
