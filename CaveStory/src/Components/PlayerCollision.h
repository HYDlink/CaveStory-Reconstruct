#ifndef PLAYERCOLLISION_H_
#define PLAYERCOLLISION_H_

#include "CollisionComponent.h"
#include "PlayerPhysics.h"
#include "../Player.h"

class PlayerCollision :public CollisionComponent {
	friend class Player;
	friend class PlayerPhysics;
public:
	const Rectangle CollisionX{ 6, 10, 20, 12 };
	const Rectangle CollisionY{ 10, 2, 12, 30 };

	PlayerCollision(Player* const player, PlayerPhysics* physics, std::shared_ptr<Map> map = NULL) :
		player_(player), physics_(physics), map_(map) {};
	
	void xCollide(units::Game deltaX);
	void yCollide(units::Game deltaY);

	Rectangle leftCollision(units::Game delta);
	Rectangle rightCollision(units::Game delta);
	Rectangle topCollision(units::Game delta);
	Rectangle bottomCollision(units::Game delta);
private:
	Player* const player_;
	PlayerPhysics *physics_;
	std::shared_ptr<Map> map_;
};
#endif // !PLAYERCOLLISION_H_