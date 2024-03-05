#include "ComponentScript.h"

ComponentScript::ComponentScript(GameObject* gameObjectPointer, string name, string initState) :Component::Component(gameObjectPointer) {
	Init(name, initState);
};

void ComponentScript::Init(string name, string initState) {
	scriptName = name;
	scriptState = initState;
}

////////////////////////BEHAVIOR FUNCTIONS////////////////////////
void ComponentScript::PlayScript() {

}

////////////////////////QUEUE FUNCTIONS////////////////////////
void ComponentScript::AddToQueue(string newInput) {
	scriptQueue.push_back(newInput);
}

string ComponentScript::ReadFront() {
	return scriptQueue[0];
}

void ComponentScript::TrashFront() {
	scriptQueue.erase(scriptQueue.begin());
}

////////////////////////STATE FUNCTIONS////////////////////////
void ComponentScript::SetState(string newState) {
	scriptState = newState;
}

string ComponentScript::GetState() {
	return scriptState;
}

////////////////////////NAME FUNCTIONS////////////////////////
string ComponentScript::GetName() {
	return scriptName;
}
