#include "Component.h"
#include "EngineObject.h"

Component::Component(EngineObject* GOPointer) {
	Init(GOPointer);
}

void Component::Init(EngineObject* GOPointer) {
	gameObjectPointer = GOPointer;
}

Component::~Component() {

}