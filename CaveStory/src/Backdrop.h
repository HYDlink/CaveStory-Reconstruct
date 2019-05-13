#ifndef BACKDROP_H_
#define BACKDROP_H_

#include "Graphics.h"

struct Backdrop {
	virtual void draw(Graphics& graphics) const = 0;
};

struct FixedBackdrop: public Backdrop {
	FixedBackdrop(Graphics& graphics, const std::string& path);
	void draw(Graphics& graphics) const;
private:
	SDL_Texture* texture_;
};

#endif // !BACKDROP_H_