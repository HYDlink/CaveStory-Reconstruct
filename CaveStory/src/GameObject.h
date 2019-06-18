#pragma once
#include "Utils/units.h"
#include <vector>
#include <memory>

// 参考 https://github.com/Clownacy/Cave-Story-Engine-2/blob/master/src/Draw.h
enum class LAYER: Uint8 {
	UI,
	HUD,
	FOREGROUND,
	PLAYER,
	ARMS,
	ENEMY,
	OBJECT,
	BACKGROUND,
	BACKDROP,
	MAX
};
class Graphics;
class GameObject {
	using ObjPtr = std::shared_ptr<GameObject>;
public:
	GameObject(LAYER l = LAYER::MAX): layer(l), isDead_(false) {}
	~GameObject() = default;
	virtual void update(units::MS deltaTime) = 0;
	virtual void draw(Graphics& graphics) const = 0;
	bool isDead() const { return isDead_; }
	bool hasChildren() const { return !children_.empty(); }

	std::vector<std::shared_ptr<GameObject>> getChildren() const {
#if 1
		return children_;
#else
		if (!hasChildren()) return std::vector<std::shared_ptr<GameObject>>();
		std::vector<std::shared_ptr<GameObject>> children;
		for (auto child : children_) {
			children.push_back(child);
			auto tmp = child->getChildren();
			children.insert(children.end(), tmp.begin(), tmp.end());
			//emplace_back原位构造，不会触发拷贝构造函数
		}
		return children;
#endif
	}
	LAYER layer;
protected:
	std::vector<ObjPtr> children_;
	bool isDead_;
};

// 根据图层对比的函数 operator< / less