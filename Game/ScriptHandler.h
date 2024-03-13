#pragma once

#include <string>
#include <vector>

//using namespace std;

class GameTimer;
class EngineObject;
class ComponentCollider;

class ScriptHandler
{
public:

	std::string scriptName;
	std::string scriptState;

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
	
	// Script Processing
	void Act();
	void QueueCheck();

	// Queue Funcs
	void EmptyQueue(std::vector<std::string> Queue);
	void UpdateQueues();

	ScriptHandler(EngineObject* objectLink, std::string name, std::string initState, GameTimer* timer);
	~ScriptHandler();

private:
	EngineObject* linkedObject;

	//lets us put aside the scriptQueue for a while if the current State is very important (ie: death)
	bool currentStatePriority;

	GameTimer* gameTimer;
	float timeStamp;

	// vectors of names for the different collisions 
	std::vector<std::string> previousCollideNames;
	std::vector<std::string> collideNames;

	// vector of script names to follow
	std::vector<std::string> scriptNames;
	
	void Init(EngineObject* linkedScript, std::string name, std::string initState, GameTimer* timer);
};