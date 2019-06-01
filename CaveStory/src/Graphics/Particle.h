#pragma once

#include "../Utils/units.h"
#include "..//Utils/PolarVector.h"
#include "..//GameObject.h"
#include "../Graphics.h"
#include "..//Sprite.h"

class Particle : public GameObject {
public:
	Particle(Position2D pos, Position2D vel, Position2D acc, units::MS lifeTime) :
		pos_(pos), vel_(vel), acc_(acc), dead_(false),
		lifeTime_(lifeTime), initTime_(SDL_GetTicks())	{}
	void loadSprite(Graphics& graphics, const std::string& filename, const SDL_Rect& clip) {
		sprite_ = std::make_shared<Sprite>(graphics, filename, clip);
	}
	void update(units::MS deltaTime) override {
		if (SDL_GetTicks() - initTime_ > lifeTime_) {
			dead_ = true;
			return;
		}
		vel_ = vel_ + acc_;
		pos_ = pos_ + vel_;
	}
	void draw(Graphics& graphics) const override {
		SDL_Renderer* renderer = graphics.getRenderer();
		Uint8 r, g, b, a;
		SDL_GetRenderDrawColor(graphics.getRenderer(), &r, &g, &b, &a);
		SDL_SetRenderDrawColor(graphics.getRenderer(), color_.r, color_.g, color_.b, color_.a);
		SDL_Rect tmp{ units::gameToPixel(pos_.x), units::gameToPixel(pos_.y), 4, 4 };
		//sprite_->draw(graphics, pos_.x, pos_.y);
		SDL_assert(SDL_RenderFillRect(graphics.getRenderer(), &tmp) != -1);
		SDL_SetRenderDrawColor(graphics.getRenderer(), r, g, b, a);
	}
	bool isDead() { return dead_; }
protected:
	Position2D pos_, vel_, acc_;
	units::MS lifeTime_;
	units::MS initTime_;
	SDL_Color color_{ 255,255,255,255 };
	std::shared_ptr<Sprite> sprite_;
	bool dead_;
};