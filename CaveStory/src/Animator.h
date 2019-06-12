#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include <map>
#include <memory>
#include "Utils/units.h"

//������ͬ��״̬�������ض���ʽ����
//����
//֧�ֶ��Animation
class Animation;
class Animator {
public:
	Animator();
	explicit Animator(std::shared_ptr<Animation> animation);
	~Animator() = default;

	void setAnimation(std::shared_ptr<Animation> animation);
	//����Ҫ����elapsedTime
	void setStates(std::size_t name, units::Frame start, units::Frame end);
	void triggerState(std::size_t name);
	
private:
	std::shared_ptr<Animation> animation_;
	//ʹ��std::size_t����Ϊ�뵽��hashֵ�������
	std::map<std::size_t, std::pair<units::Frame, units::Frame>> states_;
};


#endif // !ANIMATOR_H_