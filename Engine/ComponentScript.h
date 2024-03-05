#pragma once

#include "Component.h"

#include <string>
#include <vector>

using namespace std;

class ComponentScript: public Component
{
public:

	ComponentScript(GameObject* gameObjectPointer, string name, string initState);

	// Behavior Functions

	// Queue Functions
	void AddToQueue(string newInput); 

	// State Functions
	void SetState(string newState);
	string GetState();

	// Name Functions
	string GetName();

private:
	string scriptName;
	string scriptState;
	vector<string> scriptQueue;
	void Init(string name, string initState);
};