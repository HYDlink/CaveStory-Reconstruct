在移动或者调整窗口大小的情况下，SDL会停止工作，这样会造成一个很大的延迟时间，导致所有更新突然得到一个极大的deltaTime
这样的情况下会产生一些奇怪的毛病，比如运动体瞬间移动到很大一段距离
解决方法是使用一个最大延迟时间clamp稳定住延迟时间

## Timer

用于管理所有应用到倒计时的程序

为了同时更新所有倒计时，使用静态set保存所有Timer的指针，每次构造时将this塞入其中，析构时从中删除，Timer不可赋值/复制构造，这也是使用set的原因，视频中采用了boost库中的nocopyable

```c++
class Timer {
public:
	Timer(units::MS expirationTime, bool active = false):
		currentTime_(active? 0: expirationTime), expirationTime_(expirationTime) 
	{ timers_.insert(this); }
	~Timer() { timers_.erase(this); }

	void reset() { currentTime_ = 0; }
	bool isActive() { return currentTime_ < expirationTime_; }
	bool isExpired() { return !isActive(); }
	void update(units::MS deltaTime) { if(isActive()) currentTime_ += deltaTime; }
    
	static void updateAll(units::MS elapsed_time);
private:
	units::MS currentTime_;
	const units::MS expirationTime_;

	static std::set<Timer*> timers_;
};
```

