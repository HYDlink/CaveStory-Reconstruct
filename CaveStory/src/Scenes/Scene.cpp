#include "Scene.h"
#include "..//Camera.h"
#include "..//Player.h"
#include <SDL_events.h>
#include <algorithm>

using namespace std;

void Scene::update(units::MS deltaTime) {
	for (auto& object : objects_)
		object->update(deltaTime);
	camera_->update(deltaTime);
	auto objsToRemove = remove_if(objects_.begin(), objects_.end(), 
		[](const ObjPtr& g) { return g->isDead(); });
	objects_.erase(objsToRemove, objects_.end());
	auto sortedObjsToRemove = remove_if(sortedObjs_.begin(), sortedObjs_.end(),
		[](const ObjPtr& g) { return g->isDead(); });
	sortedObjs_.erase(sortedObjsToRemove, sortedObjs_.end());
}

void Scene::draw(Graphics& graphics) const {
	for (const auto& object : sortedObjs_)
		object->draw(graphics);
}

// TODO Player类内部包含一些HUD，它们要在此顺序绘制，
// 也就是说，得采用与更新不同的另一个数据结构用来进行绘制
void Scene::sortObjectsByLayer() {
	sortedObjs_.clear();
	for (auto obj : objects_) {
		sortedObjs_.push_back(obj);
		auto tmp = obj->getChildren();
		sortedObjs_.insert(sortedObjs_.begin(), tmp.begin(), tmp.end());
	}
	sort(sortedObjs_.begin(), sortedObjs_.end(),
		[](const ObjPtr& l, const ObjPtr& r) {
			return static_cast<int>(l->layer) > static_cast<int>(r->layer);
		});
}
