#ifndef ENEMY_H_
#define ENEMY_H_

#include "Graphics.h"
#include "Animation.h"
#include "Animator.h"

class Enemy {
public:
	Enemy(Graphics& graphics, const std::string& filename/*, units::Game xPos, units::Game yPos*/):
		animation_(std::make_shared<Animation>(graphics, filename)) {}
	virtual ~Enemy() = default;
protected:
	std::shared_ptr<Animation> animation_;
};

#endif // !ENEMY_H_