#pragma once

#include "Component.h"

#include <string>
#include <vector>

using namespace std;

class GameTimer;

class ComponentScript: public Component
{
public:

	ComponentScript(GameObject* gameObjectPointer, string name, string initState, GameTimer* timer);

	// Main Behavior Function
	void PlayScript();

	//////////////////////
	// OBJECT FUNCTIONS	//
	//////////////////////
	
	// Visibility Funcs
	void ObjectShow();
	void ObjectHide();
	void ObjectDestroy();

	// Object Shape Funcs (using the Transform struct)
	// /?\ void move(normal direction matrix, distance/magnitude)
	// /?\ void rotate
	//

	// Timer Funcs (using the GameTimer.h file)
	

	//////////////////////////
	//	SCRIPT MANAGEMENT	//
	//////////////////////////
	
	// Queue Funcs
	void AddToQueue(string newInput); 
	string ReadFront();
	void TrashFront();

	// State Funcs
	void SetState(string newState);
	string GetState();

	// Name Funcs
	string GetName();

private:
	string scriptName;
	string scriptState;

	GameTimer* gameTimer;

	vector<string> scriptQueue;
	void Init(string name, string initState, GameTimer* timer);
};