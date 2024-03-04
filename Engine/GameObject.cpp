#include "GameObject.h"

float GetDegreeToRadian(float fAngleDegree)
{
	return fAngleDegree * XM_PI / 180.f;
}

GameObject::GameObject(){}
GameObject::~GameObject(){
	if (componentList.size() > 0) {

	}
}

void GameObject::addComponent(Component* component) {
	componentList.push_back(component);
}
