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

	ComponentScript(GameObject* gameObjectPointer, string name, string initState);

	void AddToQueue(string newInput); 
	string GetName();

private:
	vector<string> scriptQueue;
	void Init(string name, string initState);
};