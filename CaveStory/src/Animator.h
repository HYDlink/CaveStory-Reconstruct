#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Animation.h"

#include <memory>

//������ͬ��״̬�������ض���ʽ����
//����
//֧�ֶ��Animation
class Animator {
public:
	Animator();
	Animator(std::shared_ptr<Animation> animation);
	~Animator() = default;

	void setAnimation(std::shared_ptr<Animation> animation);
	//����Ҫ����elapsedTime
	void setStates(std::size_t name, Uint16 start, Uint16 end);
	void triggerState(std::size_t name);
	
private:
	std::shared_ptr<Animation> animation_;
	//ʹ��std::size_t����Ϊ�뵽��hashֵ���
	std::map<std::size_t, std::pair<Uint16, Uint16>> states_;
};


#endif // !ANIMATOR_H_