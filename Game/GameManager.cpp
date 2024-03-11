#include "GameManager.h"

GameManager::GameManager() {

	Round = 1;

}

void GameManager::Play() {

	while (playing) {

		// genere une wave en fonctions du nombre de tour de boucles deja fais et il y a 2 fois le nombre d'ennemie a chaque tour
		Wave = level.initializeWave(Round * 2);


		// laisser a la fin de boucle
		Round += 1;
	}

}
