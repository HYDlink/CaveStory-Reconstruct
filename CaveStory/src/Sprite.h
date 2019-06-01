#ifndef SPRITE_H_
#define SPRITE_H_

#include <cassert>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"
#include "Utils/units.h"

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
	virtual void draw(Graphics& graphics, const SDL_Rect* srcPos, const SDL_Rect* dstPos,
		bool camIndep = false, const SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	virtual void draw(Graphics& graphics, units::Pixel desX, units::Pixel desY,
		bool camIndep = false, const SDL_RendererFlip flip = SDL_FLIP_NONE) const;
protected:
	SDL_Rect srcPos_;
private:
	SDL_Texture* texture_ = NULL;
};

bool operator== (const SDL_Rect& lhs, const SDL_Rect& rhs);
class VaryWidthSprite : public Sprite {
public:
	VaryWidthSprite(Graphics& graphics, const std::string filename,
		units::Pixel srcPosx, units::Pixel srcPosy,
		units::Pixel maxWidth, units::Pixel initialWidth,
		units::Pixel height, bool rightAlgined = false) :
		Sprite(graphics, filename, SDL_Rect{ srcPosx, srcPosy, initialWidth, height }),
		maxWidth_(maxWidth), percentage_(1.0f), rightAligned_(rightAlgined) {
	}

	// percentage is 0-1 inclusive.
	void set_percentage_width(float percentage) {
		assert(percentage >= 0.0f && percentage <= 1.0f);
		percentage_ = percentage;
		srcPos_.w = static_cast<units::Pixel>(percentage * maxWidth_);
	}

	virtual void draw(Graphics& graphics, units::Pixel desX, units::Pixel desY,
		bool camIndep = false, const SDL_RendererFlip flip = SDL_FLIP_NONE) const override {
		if (rightAligned_)
			desX = desX + static_cast<units::Pixel>((1 - percentage_) * maxWidth_);
		Sprite::draw(graphics, desX, desY, camIndep, flip);
	}
private:
	const units::Pixel maxWidth_;
	float percentage_;
	bool rightAligned_;
};

#endif