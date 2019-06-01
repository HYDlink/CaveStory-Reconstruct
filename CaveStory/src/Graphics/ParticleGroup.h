#pragma once
#include "Particle.h"
#include <vector>
#include <algorithm>

template <size_t size_>
class ParticleGroup : public GameObject{
public:
	//newTime 新建粒子的间隔时间
	ParticleGroup(Position2D spawnPos, units::MS newTime, units::MS lifeTime) :
		spawnPos_(spawnPos), newTime_(newTime), lifeTime_(lifeTime), 
		lastTime_(SDL_GetTicks()) {}

	void update(units::MS deltaTime) override {
		units::MS curTime = SDL_GetTicks();
		static Position2D acc{ 0, 0.05f };
		if (particles_.size() < size_ && curTime - lastTime_ > newTime_) {
			//抛射范围为90度角，以90度角为中心点，也就是以45度角为起始点， 可是，这不正太分布
			Position2D vel = PolarVector<units::Game>(1, 225 + 90 * rand() / RAND_MAX);
			particles_.push_back(Particle(spawnPos_, vel, acc, lifeTime_));
		}
		auto remove = std::remove_if(particles_.begin(), particles_.end(), 
			[](auto& p) { return p.isDead(); });
		particles_.erase(remove, particles_.end());
		for (auto& particle : particles_)
			particle.update(deltaTime);
	}

	void draw(Graphics& graphics) const override {
		for (auto& particle : particles_)
			particle.draw(graphics);
	}
private:
	std::vector<Particle> particles_;
	units::MS lastTime_;   // 上一次生成粒子的时间
	Position2D spawnPos_;
	units::MS lifeTime_, newTime_;
};