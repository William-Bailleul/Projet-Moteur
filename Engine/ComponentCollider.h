#pragma once

#include "Component.h"

#include <vector>
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

	// just set those to nullptr if there's none ?
	// maybe make vectors instead so it can remain empty without issue, and contain every part of the model ? 
	std::vector<BoundingSphere*> hitSpheres;
	std::vector<BoundingBox*> hitBoxes;

	ComponentCollider(GameObject* gameObjectPointer, BoundaryStyle boundaryStyle);
	~ComponentCollider();

	bool TotalCollisionCheck();

	void NewHitBox();
	void NewHitSphere();

private:
	void Init(BoundaryStyle boundaryStyle);
};

