#ifndef TIMER_H_
#define TIMER_H_

#include "units.h"
#include <set>
#include <memory>

class Timer {
public:
	Timer(units::MS expirationTime, bool active = false):
		currentTime_(active? 0: expirationTime), expirationTime_(expirationTime) 
	{ timers_.insert(this); }
	~Timer() { timers_.erase(this); }

	void reset() { currentTime_ = 0; }
	bool isActive() { return currentTime_ < expirationTime_; }
	bool isExpired() { return !isActive(); }
	units::MS currentTime() { return currentTime_; }
	static void updateAll(units::MS deltaTime);
private:
	//���ó�private�Ա�ֻ֤��timers_���ܸ�����
	void update(units::MS deltaTime) { if (isActive()) currentTime_ += deltaTime; }
	units::MS currentTime_;
	const units::MS expirationTime_;

	static std::set<Timer*> timers_;
};

#endif // !TIMER_H_