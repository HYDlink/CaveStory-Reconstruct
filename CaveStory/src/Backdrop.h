#ifndef BACKDROP_H_
#define BACKDROP_H_

#include "Graphics.h"

#if 0
struct Backdrop {
	virtual void draw(Graphics& graphics) const = 0;
};
#endif

struct FixedBackdrop: public GameObject {
	FixedBackdrop(Graphics& graphics, const std::string& path);
	FixedBackdrop(Graphics& graphics, const std::string& path, 
		units::Tile width, units::Tile height);
	void setSize(units::Tile width, units::Tile height);
	void update(units::MS deltaTime) override {}
	void draw(Graphics& graphics) const override;
private:
	SDL_Texture* texture_;
	units::Tile width_ = 0, height_ = 0;
};

#endif // !BACKDROP_H_