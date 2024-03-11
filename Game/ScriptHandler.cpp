#include "ScriptHandler.h"

//#include "ComponentScript.h"


ScriptHandler::ScriptHandler(ComponentScript* linkedScript){
	Init(linkedScript);
}

void ScriptHandler::Init(ComponentScript* linkedScript) {
	linkedObjectScript = linkedScript;
}

void ScriptHandler::Act() {
	//follow this object's script
	if (linkedObjectScript->scriptState == "un truc") {

	}
	else if (linkedObjectScript->scriptState == "un autre") {

	}
}

void ScriptHandler::QueueCheck() {
	//check the awaiting responses in the queue, deal with them
	/*
	if (linkedObjectScript.currentStatePriority == false) {

	} 
	*/
}

ScriptHandler::~ScriptHandler() {

}