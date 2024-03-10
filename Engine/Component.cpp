#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* GOPointer) {
	Init(GOPointer);
}

void Component::Init(GameObject* GOPointer) {
	gameObjectPointer = GOPointer;
}

Component::~Component() {

}