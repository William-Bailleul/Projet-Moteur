#include "ComponentScript.h"

#include "GameTimer.h"

ComponentScript::ComponentScript(GameObject* gameObjectPointer, ScriptNames name, ScriptStates initState, GameTimer* timer) :Component::Component(gameObjectPointer) {
	Init(name, initState, timer);
};

void ComponentScript::Init(ScriptNames name, ScriptStates initState, GameTimer* timer) {
	scriptName = name;
	scriptState = initState;
	gameTimer = timer;
}

// Main Behavior Function
void ComponentScript::PlayScript() {
}


//////////////////////////////////
//		OBJECT MANAGEMENT		//
//////////////////////////////////

//VISIBILITY FUNCTIONS
//make the object visible
void ComponentScript::ObjectShow() {

}

//make the object invisible
void ComponentScript::ObjectHide() {

}

//completely end the object's existence
void ComponentScript::ObjectDestroy() {

}

// OBJECT SHAPE FUNCTIONS


// TIMER FUNCTIONS


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

//STATE FUNCTIONS

void ComponentScript::SetState(ScriptStates newState) {
	scriptState = newState;
}

ScriptStates ComponentScript::GetState() {
	return scriptState;
}

//NAME FUNCTIONS

ScriptNames ComponentScript::GetName() {
	return scriptName;
}
