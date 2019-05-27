#ifndef BACKDROP_H_
#define BACKDROP_H_

#include "Graphics.h"

struct Backdrop {
	virtual void draw(Graphics& graphics) const = 0;
};

struct FixedBackdrop: public Backdrop {
	FixedBackdrop(Graphics& graphics, const std::string& path);
	FixedBackdrop(Graphics& graphics, const std::string& path, 
		units::Tile width, units::Tile height);
	void setSize(units::Tile width, units::Tile height);
	void draw(Graphics& graphics) const;
private:
	SDL_Texture* texture_;
	units::Tile width_ = 0, height_ = 0;
};

#endif // !BACKDROP_H_