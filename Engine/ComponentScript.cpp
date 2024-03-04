#include "ComponentScript.h"

ComponentScript::ComponentScript(GameObject* gameObjectPointer, string name, string initState) :Component::Component(gameObjectPointer) {
	Init(name, initState);
};

void ComponentScript::Init(string name, string initState) {
	scriptName = name;
	state = initState;
}

void ComponentScript::AddToQueue(string newInput) {
	scriptQueue.push_back(newInput);
}

string ComponentScript::GetName() {
	return scriptName;
}
