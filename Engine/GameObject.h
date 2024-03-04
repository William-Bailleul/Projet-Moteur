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
public:
	std::vector<Component*> componentList;

	GameObject();
	~GameObject();

	void addComponent(Component* component);


	//create template function to return component instance of a type
	template <typename T> T* getComponent();
	Transform m_transform;
};