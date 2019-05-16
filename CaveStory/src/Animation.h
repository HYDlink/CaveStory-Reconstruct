#pragma once
#include "Sprite.h"
#include "units.h"
#include <vector>

//TODO
//����Animator�����Animation����ʹ��״̬��
//�����������о���ͼĬ�ϵ�λ������32��Ҳ����˵��һ��SDL_Rect�������ȥ�ĵ�, ʡȥ�ܶ��鷳, ��ʱ�򿴿���
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
	units::MS elapsTime_ = 4;//ÿһ����֡�м�������ʱ��֡
};

