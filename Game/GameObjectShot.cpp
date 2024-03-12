#include "GameObjectShot.h"

GameObjectShot::GameObjectShot() : GameObject::GameObject() {
	Init();
}

void GameObjectShot::Init() {
	damage = 1;
}

int GameObjectShot::getDamage() {
	return damage;
}

GameObjectShot::~GameObjectShot() {
}
