#pragma once
#include "units.h"
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
	GameObject(LAYER l = LAYER::MAX):layer(l) {}
	~GameObject() = default;
	virtual void update(units::MS deltaTime) = 0;
	virtual void draw(Graphics& graphics) const = 0;
	bool hasChildren() const { return !children_.empty(); }
	//TODO 返回类型改为vector内含const指针
	std::vector<std::shared_ptr<GameObject>> getChildren(){
		if (!hasChildren()) return std::vector<std::shared_ptr<GameObject>>();
		std::vector<std::shared_ptr<GameObject>> children;
		for (auto child : children_) {
			children.push_back(child);
			auto tmp = child->getChildren();
			children.insert(children.end(), tmp.begin(), tmp.end());
			//emplace_back原位构造，不会触发拷贝构造函数
		}
		return children;
	}
	const LAYER layer;
protected:
	std::vector<ObjPtr> children_;
};

// 根据图层对比的函数 operator< / less