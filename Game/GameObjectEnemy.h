#pragma once
#include "GameObject.h"

class GameObjectEnemy : public GameObject
{
public:

	GameObjectEnemy();
	~GameObjectEnemy();

	void getHit(int damage);

	float posX;
	float posY;
	float posZ;

private:
	int PV;
	float speed;


	void Init();
};

