#include "Transform.h"

void Transform::Rotate(float yaw, float pitch, float roll) {
	XMVECTOR  quat;
	XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&vDir));
	XMVECTOR right = XMVector3Normalize(XMLoadFloat3(&vRight));
	XMVECTOR up = XMVector3Normalize(XMLoadFloat3(&vUp));
	quat = XMQuaternionRotationAxis(dir, roll);
	quat *= XMLoadFloat4(&qRot);
	XMStoreFloat4(&qRot, quat);
	quat = XMQuaternionRotationAxis(right, pitch);
	quat *= XMLoadFloat4(&qRot);
	XMStoreFloat4(&qRot, quat);
	quat = XMQuaternionRotationAxis(up, roll);
	quat *= XMLoadFloat4(&qRot);
	XMStoreFloat4(&qRot, quat);
	
	XMStoreFloat4x4(&mRot, XMMatrixRotationQuaternion(XMLoadFloat4(&qRot)));

	vRight.x = mRot._11;
	vRight.y = mRot._12;
	vRight.z = mRot._13;
	vUp.x = mRot._21;
	vUp.y = mRot._22;
	vUp.z = mRot._23;
	vDir.x = mRot._31;
	vDir.y= mRot._32;
	vDir.z = mRot._33;
}

void Transform::Identity() {
	mMatrix._11 = 1;
	mMatrix._12 = 0;
	mMatrix._13 = 0;
	mMatrix._21 = 0;
	mMatrix._22 = 1;
	mMatrix._23 = 0;
	mMatrix._31 = 0;
	mMatrix._32 = 0;
	mMatrix._33 = 1;
}

float GetDegreeToRadian(float fAngleDegree)
{
	return fAngleDegree * PI / 180.f;
}