#pragma once

#include "Component.h"

#include <string>
#include <vector>

//using namespace std;

class GameTimer;

class ComponentScript: public Component
{
public:

	ComponentScript(EngineObject* gameObjectPointer, std::string name, std::string initState, GameTimer* timer);

	//////////////////////
	// OBJECT FUNCTIONS	//
	//////////////////////
	
	// Visibility Funcs
	void ObjectShow();
	void ObjectHide();
	void ObjectDestroy();

	// Timer Funcs (using the GameTimer.h file)
	float GetTimeStamp();
	void SetTimeStamp();
	float HowLongSinceTimeStamp();

	//////////////////////////
	//	SCRIPT MANAGEMENT	//
	//////////////////////////
	
	// Queue Funcs
	void AddToQueue(std::string newInput);
	std::string ReadFront();
	void TrashFront();
	void EmptyQueue();

	std::string scriptName;
	std::string scriptState;

private:

	//lets us put aside the scriptQueue for a while if the current State is very important (ie: death)
	bool currentStatePriority;

	GameTimer* gameTimer; 
	float timeStamp;

	std::vector<std::string> scriptQueue;
	void Init(std::string name, std::string initState, GameTimer* timer);
};