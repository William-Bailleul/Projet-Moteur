#include "ComponentScript.h"

ComponentScript::ComponentScript(GameObject* gameObjectPointer, string name) :Component::Component(gameObjectPointer) {
	Init(name);
};

void ComponentScript::Init(string name) {
	scriptName = name;
}

void ComponentScript::AddToQueue(string newInput) {
	scriptQueue.push_back(newInput);
}

string ComponentScript::GetName() {
	return scriptName;
}
