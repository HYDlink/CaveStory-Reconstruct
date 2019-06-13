#pragma once
#include "../Utils/units.h"
#include "../Rectangle.h"
#include "../Map.h"

//TODO �����ײ��������EnterCollision���¼�����
struct CollisionInfo {
	units::Game row, col;
	bool collided;
};

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
	virtual ~CollisionComponent() = default;
	virtual bool xCollide(units::Game deltaX) = 0;
	virtual bool yCollide(units::Game deltaY) = 0;
};