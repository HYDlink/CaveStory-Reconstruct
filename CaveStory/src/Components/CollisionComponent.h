#pragma once
#include "../Utils/units.h"
#include "../Rectangle.h"
#include "../Map.h"

//TODO �����ײ��������EnterCollision���¼�����
struct CollisionInfo {
	units::Game row, col;
	bool collided;
};

class PhysicsComponent;
class CollisionComponent {
public:

	static CollisionInfo getCollisionInfo(const ForeGround& map, const Rectangle& rectangle) {
		//���Ǻܶ�,��������������ײrectangle��̫���ܿ�Խ������ͼ������
		std::vector<CollisionTile> collisions = map.getCollidingTiles(rectangle);
		CollisionInfo info{ 0, 0, false };
		for (const CollisionTile& collision : collisions) {
			if (collision.type == Map::WALL) {
				info.collided = true;
				info.row = collision.row;
				info.col = collision.col;
				break;
			}
		}
		return info;
	}

	CollisionComponent(PhysicsComponent* physics,
		const Rectangle& rectX, const Rectangle& rectY,
		std::shared_ptr<ForeGround> map = std::shared_ptr<ForeGround>()) :
		physics_(physics), CollisionX_(rectX), CollisionY_(rectY), map_(map) {
	}
	//X���Y����ײ������ȣ�ֻ����һ����ײ����
	CollisionComponent(PhysicsComponent* physics,
		const Rectangle& rectX,
		std::shared_ptr<ForeGround> map = std::shared_ptr<ForeGround>()) :
		CollisionComponent(physics, rectX, rectX, map) {}

	bool xCollide(units::Game deltaX);
	bool yCollide(units::Game deltaY);

	Rectangle xCollision() const;
	Rectangle yCollision() const;
	std::vector<Rectangle> collisions() const;
	Rectangle leftCollision(units::Game delta);
	Rectangle rightCollision(units::Game delta);
	Rectangle topCollision(units::Game delta);
	Rectangle bottomCollision(units::Game delta);
	virtual ~CollisionComponent() = default;


	const Rectangle CollisionX_;
	const Rectangle CollisionY_;
private:
	PhysicsComponent* physics_;
	std::shared_ptr<ForeGround> map_;
};