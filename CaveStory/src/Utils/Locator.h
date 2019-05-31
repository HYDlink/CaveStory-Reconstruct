#pragma once

template <typename T>
class Locator {
public:
	static T* get() { return service_; }
	static void provide(T* service) { service_ = service; }
private:
	static inline T* service_;
};