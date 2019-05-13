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
		//�����ظ�������, ����elapsTime, �����Ժ���õ����ٵĹ���, ������Ҫ�������ڵ�֡λ�ò���
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
		currentFrame_ = startFrame_;//ѭ��
		currentTime_ = 0;
		//�����е������⣬���currentFrame_����endFrame_�Ļ�, ��ô�����Ķ�����������һ��ʱ��֡...
	}
}

void Animation::draw(Graphics& graphics, SDL_Rect* dstPos) {
	Sprite::draw(graphics, &frames_[currentFrame_], dstPos);
}
