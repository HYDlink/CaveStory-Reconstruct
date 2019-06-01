#include "Scene.h"
#include "..//Camera.h"
#include "..//Player.h"
#include <SDL_events.h>

using namespace std;

void Scene::update(units::MS deltaTime) {
	for (auto& object : objects_)
		object->update(deltaTime);
	camera_->update(deltaTime);
}

void Scene::draw(Graphics& graphics) const {
	for (const auto& object : sortedObjs_)
		object->draw(graphics);
}

// TODO Player类内部包含一些HUD，它们要在此顺序绘制，
// 也就是说，得采用与更新不同的另一个数据结构用来进行绘制
void Scene::sortObjectsByLayer() {
	using ObjectPtr = shared_ptr<GameObject>;
	sortedObjs_.clear();
	for (auto obj : objects_) {
		sortedObjs_.push_back(obj);
		auto tmp = obj->getChildren();
		sortedObjs_.insert(sortedObjs_.begin(), tmp.begin(), tmp.end());
	}
	sort(sortedObjs_.begin(), sortedObjs_.end(),
		[](const ObjectPtr& l, const ObjectPtr& r) {
			return static_cast<int>(l->layer) > static_cast<int>(r->layer);
		});
}
