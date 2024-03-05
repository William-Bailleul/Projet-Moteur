#include "ComponentScript.h"

ComponentScript::ComponentScript(GameObject* gameObjectPointer, string name, string initState) :Component::Component(gameObjectPointer) {
	Init(name, initState);
};

void ComponentScript::Init(string name, string initState) {
	scriptName = name;
	scriptState = initState;
}

void ComponentScript::AddToQueue(string newInput) {
	scriptQueue.push_back(newInput);
}

void ComponentScript::SetState(string newState) {
	scriptState = newState;
}

string ComponentScript::GetState() {
	return scriptState;
}

string ComponentScript::GetName() {
	return scriptName;
}
