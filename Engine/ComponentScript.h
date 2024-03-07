#pragma once

#include "Component.h"

//#include <string>
#include <vector>

//using namespace std;

class GameTimer;

enum ScriptNames {
	dada
};

enum ScriptStates {

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

	// Timer Funcs (using the GameTimer.h file)
	__int64 GetTimeStamp();
	void SetTimeStamp();
	__int64 HowLongSinceTimeStamp();

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
	__int64 timeStamp;

	std::vector<ScriptNames> scriptQueue;
	void Init(ScriptNames name, ScriptStates initState, GameTimer* timer);
};