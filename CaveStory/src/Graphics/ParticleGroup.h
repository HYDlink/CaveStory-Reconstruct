#pragma once
#include "Particle.h"
#include <vector>
#include <algorithm>

template <size_t size_>
class ParticleGroup : public GameObject{
public:
	//newTime �½����ӵļ��ʱ��
	ParticleGroup(Position2D spawnPos, units::MS newTime, units::MS lifeTime) :
		spawnPos_(spawnPos), newTime_(newTime), lifeTime_(lifeTime), 
		lastTime_(SDL_GetTicks()) {}

	void update(units::MS deltaTime) override {
		units::MS curTime = SDL_GetTicks();
		static Position2D acc{ 0, 0.05f };
		if (particles_.size() < size_ && curTime - lastTime_ > newTime_) {
			//���䷶ΧΪ90�Ƚǣ���90�Ƚ�Ϊ���ĵ㣬Ҳ������45�Ƚ�Ϊ��ʼ�㣬 ���ǣ��ⲻ��̫�ֲ�
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
	units::MS lastTime_;   // ��һ���������ӵ�ʱ��
	Position2D spawnPos_;
	units::MS lifeTime_, newTime_;
};