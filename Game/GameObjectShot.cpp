#include "GameObjectShot.h"

GameObjectShot::GameObjectShot() : GameObject::GameObject() {
	Init();
}

void GameObjectShot::Init() {
	damage = 1;
}

GameObjectShot::~GameObjectShot() {
}
