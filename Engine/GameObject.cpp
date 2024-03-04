#include "GameObject.h"


GameObject::GameObject(){}
GameObject::~GameObject(){
	if (componentList.size() > 0) {

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
