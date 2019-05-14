#include "Animator.h"


using namespace std;


Animator::Animator() {
}

Animator::Animator(std::shared_ptr<Animation> animation): animation_(animation) {}

void Animator::setAnimation(std::shared_ptr<Animation> animation) {
	animation_ = animation;
}

void Animator::setStates(std::size_t name, Uint16 start, Uint16 end) {
	if (end <= start)
		std::swap(end, start);
	if (end > animation_->getFrames()) {
		cerr << "out of Animation frame range" << endl;
		return;
	}
	states_[name] = make_pair(start, end);
}

void Animator::triggerState(std::size_t name) {
	if (states_.count(name) != 0)
		animation_->start_Animation(states_[name].first, states_[name].second, 6, true);
}
