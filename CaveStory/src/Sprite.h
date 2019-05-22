#ifndef SPRITE_H_
#define SPRITE_H_

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"

class Sprite
{
public:
	Sprite(Graphics& graphics, const std::string& filename);
	Sprite(Graphics& graphics, const std::string& filename, const SDL_Rect& clip);

	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	Sprite& operator=(const Sprite&) = default;
	Sprite& operator=(Sprite&&) = default;
	virtual ~Sprite();

	void reset();
	void reset(Graphics& graphics, const std::string& filename, const SDL_Rect& clip);
	SDL_Texture* getTexture() { return texture_; }
	void draw(Graphics& graphics, SDL_Rect* srcPos, SDL_Rect* dstPos,
		const SDL_RendererFlip flip = SDL_FLIP_NONE);
protected:
	SDL_Rect srcPos_;
private:
	SDL_Texture* texture_ = NULL;
};

bool operator== (const SDL_Rect& lhs, const SDL_Rect& rhs);

#endif