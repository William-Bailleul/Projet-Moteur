#pragma once

#include "Component.h"

//#include <string>
#include <vector>

//using namespace std;

class GameTimer;

enum ScriptNames
{
	tmp2
enum ScriptNames {
};

enum ScriptStates {
	tmp
};

class ComponentScript: public Component
{
public:

	ComponentScript(GameObject* gameObjectPointer, ScriptNames name, ScriptStates initState, GameTimer* timer);

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
	void AddToQueue(ScriptNames newInput);
	ScriptNames ReadFront();
	void TrashFront();

	// State Funcs
	void SetState(ScriptStates newState);
	ScriptStates GetState();

	// Name Funcs
	ScriptNames GetName();

private:
	ScriptNames scriptName;
	ScriptStates scriptState;

	//lets us put aside the scriptQueue for a while if the current State is very important (ie: death, 
	int currentStatePriority;

	GameTimer* gameTimer;

	std::vector<ScriptNames> scriptQueue;
	void Init(ScriptNames name, ScriptStates initState, GameTimer* timer);
};