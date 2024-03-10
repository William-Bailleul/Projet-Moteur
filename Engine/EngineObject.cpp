#include "EngineObject.h"

#include "Component.h"

EngineObject::EngineObject(int posX, int posY, int posZ){
	Init(posX, posY, posZ);
}

EngineObject::~EngineObject(){
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			delete(componentList[0]);
		}
	}
}

void EngineObject::Init(int posX, int posY, int posZ) {
	m_posX = posX;
	m_posY = posY;
	m_posZ = posZ;
}

void EngineObject::addComponent(Component* component) {
	componentList.push_back(component);
}