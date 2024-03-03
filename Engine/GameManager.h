#pragma once

#include <vector>

class GameObject;

class GameManager
{
	std::vector<GameObject*> objectList;

	GameManager();
	~GameManager();

};

