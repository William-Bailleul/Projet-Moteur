#pragma once

class GameObject;

class Component
{
public:
	GameObject* gameObjectPointer;

	Component(GameObject* gameObjectPointer);

private:
	void Init(GameObject* gameObjectPointer);
};

