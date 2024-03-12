#include "ComponentScript.h"

#include "EngineTimer.h"
#include "Transform.h"
#include "EngineObject.h"

ComponentScript::ComponentScript(EngineObject* gameObjectPointer, std::string name, std::string initState, GameTimer* timer) : Component(gameObjectPointer) {
	Init(name, initState, timer);
};

void ComponentScript::Init(std::string name, std::string initState, GameTimer* timer) {
	scriptName = name;
	scriptState = initState;
	gameTimer = timer;
	currentStatePriority = false;
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
float ComponentScript::GetTimeStamp() {
	return timeStamp;
}

//set the saved timeStamp to current time
void ComponentScript::SetTimeStamp() {
	timeStamp = gameTimer->TotalTime();
}

//get how long it have been since you saved the timeStamp
float ComponentScript::HowLongSinceTimeStamp() {
	float diff = (gameTimer->TotalTime() - timeStamp);
	return diff;
}

//////////////////////////////////
//		SCRIPT MANAGEMENT		//
//////////////////////////////////

//QUEUE FUNCTIONS

void ComponentScript::AddToQueue(std::string newInput) {
	scriptQueue.push_back(newInput);
}

std::string ComponentScript::ReadFront() {
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

