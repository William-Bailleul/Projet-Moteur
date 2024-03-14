#pragma once
#include "GameObjectEnemy.h"
#include "GameObjectShot.h"
#include <vector>

using namespace std;

class GameObject
{
public:
	vector<GameObjectEnemy> EnemyList;
	vector<GameObjectShot> ShotList;
	
};

