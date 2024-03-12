#include "GameObjectEnemy.h"

GameObjectEnemy::GameObjectEnemy() : GameObject::GameObject() {
	Init();
}

void GameObjectEnemy::Init() {
	PV = 1;
	speed = 1.0;
	// mettre en place lien avec son modele 3d des que possible
}

void GameObjectEnemy::getHit(int d) {
	PV -= d;
	if (PV == 0) {
		// detruire l'ennemie et son 3d
	}
}

GameObjectEnemy::~GameObjectEnemy() {
}
