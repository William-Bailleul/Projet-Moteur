#pragma once

class EngineObject;

class Component
{
public:
	EngineObject* gameObjectPointer;

	Component(EngineObject* gameObjectPointer);
	~Component();

private:
	void Init(EngineObject* gameObjectPointer);
};

