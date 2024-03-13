#pragma once

#include "Component.h"

//#include <string>
#include <vector>

//using namespace std;

class GameTimer;

enum ScriptNames {

};

enum ScriptStates {

};

class ComponentScript: public Component
{
public:

	ComponentScript(EngineObject* gameObjectPointer, ScriptNames name, ScriptStates initState, GameTimer* timer);

	// Main Behavior Function
	void ScriptSelector();

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
	void EmptyQueue();

	// Name Funcs
	ScriptNames GetName();

private:
	ScriptNames scriptName;
	ScriptStates scriptState;

	//lets us put aside the scriptQueue for a while if the current State is very important (ie: death)
	int currentStatePriority;

	GameTimer* gameTimer; 
	__int64 timeStamp;

	std::vector<ScriptNames> scriptQueue;
	void Init(ScriptNames name, ScriptStates initState, GameTimer* timer);
};