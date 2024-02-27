#include "Transform.h"

void Transform::Rotate(float yaw, float pitch, float roll) {
	XMVECTOR  quat;
	quat = XMQuaternionRotationAxis(vDir, roll);
	qRot = quat;
	quat = XMQuaternionRotationAxis(vRight, pitch);
	qRot *= quat;
	quat = XMQuaternionRotationAxis(vUp, roll);
	qRot *= quat;

	
}
