#include "GameObject.h"

float GetDegreeToRadian(float fAngleDegree)
{
	return fAngleDegree * XM_PI / 180.f;
}

GameObject::GameObject(){}
GameObject::~GameObject(){
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			delete(componentList[0]);
		}
	}
}

void GameObject::addComponent(Component* component) {
	componentList.push_back(component);
}

template <typename T> T* GameObject::getComponent() {
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			if (typeid(componentList[i]) == typeid(T)) {
				return componentList[i];
			}
		}
	}
	return nullptr;
}