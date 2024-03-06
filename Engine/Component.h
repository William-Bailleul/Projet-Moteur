#pragma once

class GameObject;

class Component
{
public:
	GameObject* gameObjectPointer;

	Component(GameObject* gameObjectPointer);
	~Component();

private:
	void Init(GameObject* gameObjectPointer);
};

