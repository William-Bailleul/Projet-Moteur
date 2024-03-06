#include "ComponentScript.h"

#include "GameTimer.h"

ComponentScript::ComponentScript(GameObject* gameObjectPointer, string name, string initState, GameTimer* timer) :Component::Component(gameObjectPointer) {
	Init(name, initState, timer);
};

void ComponentScript::Init(string name, string initState, GameTimer* timer) {
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

void ComponentScript::AddToQueue(string newInput) {
	scriptQueue.push_back(newInput);
}

string ComponentScript::ReadFront() {
	return scriptQueue[0];
}

void ComponentScript::TrashFront() {
	scriptQueue.erase(scriptQueue.begin());
}

//STATE FUNCTIONS

void ComponentScript::SetState(string newState) {
	scriptState = newState;
}

string ComponentScript::GetState() {
	return scriptState;
}

//NAME FUNCTIONS

string ComponentScript::GetName() {
	return scriptName;
}
