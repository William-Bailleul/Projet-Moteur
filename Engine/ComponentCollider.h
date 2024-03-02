#pragma once

#include "Component.h"

#include <DirectXCollision.h>

using namespace DirectX;

class ComponentCollider : public Component
{
public:
	enum BoundaryStyle
	{
		RECT,
		BOX,
		SPHERE
	};

	BoundingSphere* hitsphere;
	BoundingBox* hitbox;

	ComponentCollider(GameObject* gameObjectPointer, BoundaryStyle boundaryStyle);

private:
	void Init(BoundaryStyle boundaryStyle);
};

