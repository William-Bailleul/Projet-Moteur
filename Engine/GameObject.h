#pragma once
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include<vector>

#define PI 3.14159265358979323846264338327950288

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
};