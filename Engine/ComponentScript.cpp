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

// Main Behavior Function
/* 
Remember that this function operates ONCE EVERY FRAME,
which means we have to base our functions on time or we
would get different game speeds based on the framerate
*/
void ComponentScript::PlayScript() {

	//check the queue ?

	//switch (scriptState) {

	//}
}


//////////////////////////////////
//		OBJECT MANAGEMENT		//
//////////////////////////////////

//VISIBILITY FUNCTIONS
//make the object visible
void ComponentScript::ObjectShow() {

}

//for ^^^ those vvv two, play around with the display pipeline idk

//make the object invisible
void ComponentScript::ObjectHide() {

}

//completely end the object's existence
void ComponentScript::ObjectDestroy() {
	// /kill @p :)
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
