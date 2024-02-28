#pragma once

#include "Component.h"

class ComponentScript: public Component
{
public:
	ComponentScript(GameObject* gameObjectPointer);

private:
	void Init();
};