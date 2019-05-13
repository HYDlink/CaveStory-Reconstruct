#include "Player.h"

using namespace std;


Player::Player(Graphics& graphics, const string& filename)
	: clipRects_(CharTypeSprites, vector<SDL_Rect>(MotionSprites)), xPos_(0), yPos_(0) {
	setClipRect();
	animation_ = make_shared<Animation>(graphics, filename, clipRects_[0]);
	setAimator();
}


Player::~Player() {
}

void Player::setClipRect() {
	Uint8 width = 32;
	for(int i = 0; i < CharTypeSprites; ++i)
		for (int j = 0; j < MotionSprites; ++j) {
			clipRects_[i][j] = SDL_Rect{ j * width, i * width, width, width };
		}
}

void Player::setAimator() {
	animation_->start_Animation(0, 2, 4, true);
}

void Player::update() {
	animation_->update();
}

void Player::draw(Graphics& graphics) {
	SDL_Rect pos{ xPos_, yPos_, 0, 0 };
	animation_->draw(graphics, &pos);
}
