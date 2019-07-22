#include "Scene.h"
#include "..//Camera.h"
#include "..//Player.h"
#include <SDL_events.h>
#include <algorithm>

using namespace std;

Scene::Scene() {}

void Scene::update(units::MS deltaTime) {
	for (auto& object : sortedObjs_)
		object->update(deltaTime);
	camera_->update(deltaTime);
	//销毁死亡GameObject, TODO 销毁子类
	auto objsToRemove = remove_if(objects_.begin(), objects_.end(), 
		[](const ObjPtr& g) { return g->isDead(); });
	objects_.erase(objsToRemove, objects_.end());
	auto sortedObjsToRemove = remove_if(sortedObjs_.begin(), sortedObjs_.end(),
		[](const ObjPtr& g) { return g->isDead(); });
	sortedObjs_.erase(sortedObjsToRemove, sortedObjs_.end());
	//处理可能新加入的Objects
	sortObjectsByLayer();
}

void Scene::draw(Graphics& graphics) const {
	for (const auto& object : sortedObjs_)
		object->draw(graphics);
}

void Scene::getAllObjects(std::vector<ObjPtr> objs) {
	if (objs.empty()) return;
	sortedObjs_.insert(sortedObjs_.begin(), objs.begin(), objs.end());
	for (auto obj : objs)
		getAllObjects(obj->getChildren());
}

void Scene::sortObjectsByLayer() {
	sortedObjs_.clear();
	getAllObjects(objects_);
	if (sortedObjs_.size() == 1) return;
	sort(sortedObjs_.begin(), sortedObjs_.end(),
		[](const ObjPtr& l, const ObjPtr& r) {
			return static_cast<int>(l->layer) > static_cast<int>(r->layer);
		});
}
