#ifndef PLAYER_H_
#define PLAYER_H_

#include "Animation.h"
#include <vector>
#include <memory>

class Player {
public:
	const Uint8 MotionSprites = 11;
	const Uint8 CharTypeSprites = 12;
	Player(Graphics& graphics, const std::string& filename);
	~Player();

	void setClipRect();
	void setAimator();
	void update();
	void draw(Graphics& graphics);
private:
	std::shared_ptr<Animation> animation_;
	std::vector<std::vector<SDL_Rect>> clipRects_;
	Uint8 xPos_, yPos_;
};

#endif // !PLAYER_H_