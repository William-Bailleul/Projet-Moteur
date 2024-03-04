#pragma once

#include "Component.h"

#include <string>
#include <vector>

using namespace std;

class ComponentScript: public Component
{
public:
	string scriptName;
	string state;
	vector<string> scriptQueue;

	ComponentScript(GameObject* gameObjectPointer, string name, string initState);

	void AddToQueue(string newInput); 
	string GetName();

private:
	void Init(string name, string initState);
};