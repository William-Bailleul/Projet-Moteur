#include "ComponentScript.h"

#include "GameTimer.h"
#include "Transform.h"

using namespace std;

ComponentScript::ComponentScript(GameObject* gameObjectPointer, ScriptNames name, ScriptStates initState, GameTimer* timer) : Component(gameObjectPointer) {
	Init(name, initState, timer);
};

void ComponentScript::Init(ScriptNames name, ScriptStates initState, GameTimer* timer) {
	scriptName = name;
	scriptState = initState;
	gameTimer = timer;
}


//////////////////////////////////
//		OBJECT MANAGEMENT		//
//////////////////////////////////

//VISIBILITY FUNCTIONS
//make the object visible
void ComponentScript::ObjectShow() {

}

//for ^^^ those vvv two, play around with the display list once it works

//make the object invisible
void ComponentScript::ObjectHide() {

}

//completely end the object's existence
void ComponentScript::ObjectDestroy() {
	// /kill @p :)
}

// TIMER FUNCTIONS
//get the saved timeStamp
__int64 ComponentScript::GetTimeStamp() {
	return timeStamp;
}

//set the saved timeStamp to current time
void ComponentScript::SetTimeStamp() {
	timeStamp = gameTimer->TotalTime();
}

//get how long it have been since you saved the timeStamp
__int64 ComponentScript::HowLongSinceTimeStamp() {
	__int64 diff = (gameTimer->TotalTime() - timeStamp);
	return diff;
}

//////////////////////////////////
//		SCRIPT MANAGEMENT		//
//////////////////////////////////

//QUEUE FUNCTIONS

void ComponentScript::AddToQueue(ScriptNames newInput) {
	scriptQueue.push_back(newInput);
}

ScriptNames ComponentScript::ReadFront() {
	return scriptQueue[0];
}

void ComponentScript::TrashFront() {
	scriptQueue.erase(scriptQueue.begin());
}

void ComponentScript::EmptyQueue() {
	for (int i = 0; i < scriptQueue.size(); i++) {
		TrashFront();
	}
}

//NAME FUNCTIONS

ScriptNames ComponentScript::GetName() {
	return scriptName;
}
