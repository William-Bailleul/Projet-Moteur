#pragma once

#include <vector>

class GameObject;

class GameManager
{
public:
	std::vector<GameObject*> objectList;

	GameManager();
	~GameManager();

};

