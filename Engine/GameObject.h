#pragma once
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include<vector>
#include "Transform.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

class Component;

class GameObject
{
private:
	int m_posX;
	int m_posY;
	int m_posZ;
public:
	std::vector<Component*> componentList;

	GameObject();
	~GameObject();

	void Init(int posX, int posY, int posZ);
	void addComponent(Component* component);


	//create template function to return component instance of a type
	template <typename T> T* getComponent();
	Transform m_transform;
};

template <typename T>
T* GameObject::getComponent() {
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			if (typeid(componentList[i]) == typeid(T*)) {
				return (T*) componentList[i];
			}
		}
	}
	return nullptr;
}