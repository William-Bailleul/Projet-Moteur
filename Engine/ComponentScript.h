#pragma once

#include "Component.h"

#include <string>
#include <vector>

using namespace std;

class ComponentScript: public Component
{
public:
	string scriptName;
	vector<string> scriptQueue;

	ComponentScript(GameObject* gameObjectPointer, string name);

	void AddToQueue(string newInput); 
	string GetName();

private:
	void Init(string name);
};