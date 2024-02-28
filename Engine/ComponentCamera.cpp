#include "ComponentCamera.h"


ComponentCamera::ComponentCamera(GameObject* gameObjectPointer, float fovAngle, float ratio, float near, float far) : Component::Component(gameObjectPointer){
	Init(fovAngle, ratio, near, far);
}

void ComponentCamera::Init(float fovAngle, float ratio, float near, float far){
	fovAngleY = fovAngle;
	aspectRatio = ratio;
	nearZ = near;
	farZ = far;
}