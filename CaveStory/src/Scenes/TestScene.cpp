#include "TestScene.h"
#include "../Utils/TestObject.h"

using namespace std;
TestScene::TestScene() : Scene() {
	init(); sortObjectsByLayer();
}

void TestScene::init() {
	shared_ptr<TestObject> testobj_;
	objects_.emplace_back(testobj_);
}

void TestScene::update(units::MS deltaTime) {
}

void TestScene::handleEvent(SDL_Event* e) {
}
