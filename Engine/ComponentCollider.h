#pragma once

#include "Component.h"

class ComponentCollider : public Component
{
public:
	ComponentCollider(GameObject* gameObjectPointer);

private:
	void Init();
};

