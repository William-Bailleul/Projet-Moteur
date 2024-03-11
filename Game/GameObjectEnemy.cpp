#include "GameObjectEnemy.h"

GameObjectEnemy::GameObjectEnemy() : GameObject::GameObject() {
	Init();
}

void GameObjectEnemy::Init() {
	PV = 1;
	speed = 1.0;
}

GameObjectEnemy::~GameObjectEnemy() {
}
