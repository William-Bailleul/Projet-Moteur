#pragma once
#include <DirectXPackedVector.h>
#include <iostream>
#include<vector>

#include "Transform.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

class Component;

class EngineObject
{
public:
	std::vector<Component*> componentList;
	Transform m_transform;

	EngineObject();
	~EngineObject();

	void Init();
	void addComponent(Component* component);

	//create template function to return component instance of a type
	template <typename T> T* getComponent();
};

template <typename T> 
T* EngineObject::getComponent() {
	if (componentList.size() > 0) {
		for (int i = 0; i < componentList.size(); i++) {
			if (typeid(componentList[i]) == typeid(T*)) {
				return (T*) componentList[i];
			}
		}
	}
	return nullptr;
}