#pragma once
#include "GameObjectEnemy.h"
#include "GameObjectShot.h"
#include "GameScripts.h"
#include "Input.h"
#include "LevelManager.h"
#include "TimeManager.h"
#include <vector>

using namespace std;

LevelManager level;

class GameManager
{
private:
	vector<vector<float>> Wave;

	int Round;

	bool playing;

	GameManager();

	void Play();

};

