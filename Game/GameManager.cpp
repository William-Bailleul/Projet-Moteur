#include "GameManager.h"

GameManager::GameManager() {

	Round = 1;

}

void GameManager::Play() {

	while (playing) {

		// when shot 
		Object.ShotList.push_back(GameObjectShot::GameObjectShot());

		// genere une wave en fonctions du nombre de tour de boucles deja fais et il y a 2 fois le nombre d'ennemie a chaque tour
		Wave = level.initializeWave(Round * 2);
		for (int i = 0; i < Round * 2; i++) {
			Object.EnemyList.push_back(GameObjectEnemy::GameObjectEnemy());
			Object.EnemyList[i].posX = Wave[i][0];
			Object.EnemyList[i].posY = Wave[i][1];
			Object.EnemyList[i].posZ = Wave[i][2];
		}

		//quand il y a colision entre un ennemi et un tire
		Object.EnemyList[0].getHit(Object.ShotList[0].getDamage());

		// laisser a la fin de boucle
		Round += 1;
	}

}
GameManager::GameManager() {}

//GameManager::~GameManager() {}
