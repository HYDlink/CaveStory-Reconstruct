#include "Timer.h"
std::set<Timer*> Timer::timers_;

void Timer::updateAll(units::MS deltaTime) {
	for (auto* timer : timers_) 
		timer->update(deltaTime);
}
