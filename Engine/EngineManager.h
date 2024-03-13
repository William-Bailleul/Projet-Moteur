#pragma once

#include <vector>

class EngineObject;
class Renderer;

class EngineManager
{
public:
	std::vector<EngineObject*> objectList;
	Renderer* gameRenderer;

	//EngineManager();
	//~EngineManager();

};

