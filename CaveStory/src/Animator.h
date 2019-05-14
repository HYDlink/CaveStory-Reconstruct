#ifndef ANIMATOR_H_
#define ANIMATOR_H_

#include "Animation.h"

#include <memory>

//建立不同的状态，并以特定方式命名
//触发
//支持多个Animation
class Animator {
public:
	Animator();
	Animator(std::shared_ptr<Animation> animation);
	~Animator() = default;

	void setAnimation(std::shared_ptr<Animation> animation);
	//可能要设置elapsedTime
	void setStates(std::size_t name, Uint16 start, Uint16 end);
	void triggerState(std::size_t name);
	
private:
	std::shared_ptr<Animation> animation_;
	//使用std::size_t是因为想到了hash值这个
	std::map<std::size_t, std::pair<Uint16, Uint16>> states_;
};


#endif // !ANIMATOR_H_