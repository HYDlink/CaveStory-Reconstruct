#ifndef ENEMY_H_
#define ENEMY_H_

#include "Graphics/Graphics.h"
#include "Graphics/Animation.h"
#include "Animator.h"
#include "GameObject.h"

class Enemy : public GameObject {
public:
	Enemy(Graphics& graphics, const std::string& filename/*, units::Game xPos, units::Game yPos*/):
		GameObject(LAYER::ENEMY),
		animation_(std::make_shared<Animation>(graphics, filename)) {}
	virtual ~Enemy() = default;
	virtual void update(units::MS deltaTime) = 0;
	virtual void draw(Graphics& graphics) const = 0;
protected:
	std::shared_ptr<Animation> animation_;
};

#endif // !ENEMY_H_