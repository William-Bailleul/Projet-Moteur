#include "Component.h"

Component::Component(GameObject* GOPointer) {
	Init(GOPointer);
}

void Component::Init(GameObject* GOPointer) {
	gameObjectPointer = GOPointer;
}

Component::~Component() {

}