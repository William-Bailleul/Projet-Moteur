#include "ScriptHandler.h"

/*
#include "Engine.lib/EngineTimer.h"
#include "Engine.lib/EngineObject.h"
#include "Engine.lib/ComponentCollider.h"
#include "Engine.lib/Transform.h"
*/

ScriptHandler::ScriptHandler(EngineObject* objectLink, std::string name, std::string initState, GameTimer* timer){
	Init(objectLink, name, initState, timer);
}

void ScriptHandler::Init(EngineObject* objectLink, std::string name, std::string initState, GameTimer* timer) {
	linkedObject = objectLink;	
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
void ScriptHandler::ObjectShow() {
}

//for ^^^ those vvv two, play around with the display list once it works

//make the object invisible
void ScriptHandler::ObjectHide() {
}

//completely end the object's existence
void ScriptHandler::ObjectDestroy() {
}

// TIMER FUNCTIONS
//get the saved timeStamp
float ScriptHandler::GetTimeStamp() {
	return timeStamp;
}

//set the saved timeStamp to current time
void ScriptHandler::SetTimeStamp() {
//	timeStamp = gameTimer->TotalTime();
}

//get how long it have been since you saved the timeStamp
float ScriptHandler::HowLongSinceTimeStamp() {
//	float diff = (gameTimer->TotalTime() - timeStamp);
//	return diff;
}

//////////////////////////////////
//		SCRIPT MANAGEMENT		//
//////////////////////////////////

//QUEUE FUNCTIONS

void ScriptHandler::EmptyQueue(std::vector<std::string> Queue) {
	for (int i = 0; i < Queue.size(); i++) {
		Queue.erase(Queue.begin());
	}
}

void ScriptHandler::UpdateCollisionLists() {
	/*
	ComponentCollider* objectCollider = linkedObject->GetComponent<ComponentCollider>();

	//acquire new data from object's collider
	// distribute it to the script names lists
	for (int i = 0; i > objectCollider->currentHitNames.size(); i++) {
		if (std::count(scriptNamesList.begin(), scriptNamesList.end(), objectCollider->currentHitNames[i]) == 0) {
			scriptNamesList.push_back(objectCollider->currentHitNames[i]);
		}
	}
	*/
}

//BEHAVIOR FUNCTIONS

void ScriptHandler::Act() {
	//follow this object's script
	
	
	if (scriptState == "Destroy") {
		ObjectDestroy();
	}
	else if (scriptState == "BulletMove") {
		//script that makes bullets go forward, using their direction values
		//linkedObject->transform->translate(linkedObject.dirX, linkedObject.dirY, linkedObject.dirZ);
	}
	else if (scriptState == "un autre") {

	}
	
}

void ScriptHandler::QueueCheck() {
	//check the awaiting responses in the queue, deal with them
	
	//make sure the current state doesnt have priority
	if (currentStatePriority == false) {

	} 
	
}

ScriptHandler::~ScriptHandler() {

}
