#pragma once

#include "Component.h"

class ComponentCamera : public Component
{
public:
	float fovAngleY; // vertical field of view angle in radians
	float aspectRatio; // aspect ratio = width / height
	float nearZ; // distance to near plane
	float farZ; // distance to far plane

	ComponentCamera(GameObject* gameObjectPointer, float fovAngle, float ratio, float near, float far);

private:
	void Init(float fovAngle, float ratio, float near, float far);
};

