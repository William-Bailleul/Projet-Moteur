#include "GameObject.h"

#include "Component.h"

GameObject::GameObject(int posX, int posY, int posZ){
	Init(posX, posY, posZ);
}

GameObject::~GameObject(){
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			delete(componentList[0]);
		}
	}
}

void GameObject::Init(int posX, int posY, int posZ) {
	m_posX = posX;
	m_posY = posY;
	m_posZ = posZ;
}

void GameObject::addComponent(Component* component) {
	componentList.push_back(component);
}