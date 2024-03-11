#pragma once
#include "GameObject.h"

class GameObjectEnemy : public GameObject
{
public:

	GameObjectEnemy();
	~GameObjectEnemy();

private:
	int PV;
	float speed;

	void Init();
};

