#pragma once
#include "GameObject.h"
class GameObjectShot : public GameObject
{
public:
	GameObjectShot();
	~GameObjectShot();

	int getDamage();

private:
	int damage;

	void Init();
};

