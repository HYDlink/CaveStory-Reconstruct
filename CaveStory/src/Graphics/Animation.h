#pragma once
#include "Sprite.h"
#include "../Utils/units.h"
#include <vector>

//TODO
//����Animator�����Animation����ʹ��״̬��
//�����������о���ͼĬ�ϵ�λ������32��Ҳ����˵��һ��SDL_Rect�������ȥ�ĵ�, ʡȥ�ܶ��鷳, ��ʱ�򿴿���
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

	// bg��ed������Ϊ0���߷Ƿ�ֵ��ʼĬ�����еĶ���
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
	units::MS elapsTime_ = 4;//ÿһ����֡�м�������ʱ��֡
};

