#include "TestObject.h"
#include "Math.h"
#include "../Graphics/Graphics.h"


void TestObject::update(units::MS deltaTime) {

	//increment timer once per frame
	currentLerpTime += deltaTime;
	if (currentLerpTime > lerpTime) {
		currentLerpTime = lerpTime;
	}

	//lerp!
	float perc = currentLerpTime / lerpTime;
	pos_.x = lerp(startPos.x, endPos.x, perc);
}

void TestObject::draw(Graphics& graphics) const {
	auto renderer = graphics.getRenderer();
	SDL_Color color_{ 255, 255,255,255 };
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	SDL_SetRenderDrawColor(renderer, color_.r, color_.g, color_.b, color_.a);
	SDL_Rect rect{ pos_.x, pos_.y, units::TileSize, units::TileSize };
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
