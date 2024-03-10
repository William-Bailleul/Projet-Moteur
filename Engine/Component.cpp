#include "Component.h"
#include "EngineObject.h"

Component::Component(GameObject* GOPointer) {
	Init(GOPointer);
}

void Component::Init(GameObject* GOPointer) {
	gameObjectPointer = GOPointer;
}

Component::~Component() {

}