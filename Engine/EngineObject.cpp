#include "EngineObject.h"

#include "Component.h"

EngineObject::EngineObject(){
	Init();
}

EngineObject::~EngineObject(){
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			delete(componentList[0]);
		}
	}
}

void EngineObject::Init() {
}

void EngineObject::addComponent(Component* component) {
	componentList.push_back(component);
}