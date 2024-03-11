#pragma once
#include "GameObject.h"
class GameObjectShot : public GameObject
{
	GameObjectShot();
	~GameObjectShot();

private:
	int damage;

	void Init();
};

