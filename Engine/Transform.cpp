#include "Transform.h"

Transform::Transform()
{
	Identity();
}

void Transform::Identity() {
	// initialise scale
	vSca.x = 1.0f;
	vSca.y = 1.0f;
	vSca.z = 1.0f;
	XMStoreFloat4x4(&mSca, XMMatrixIdentity());

	// initialise rotation
	vRight.x = 1.0f;
	vRight.y = 0.0f;
	vRight.z = 0.0f;
	vUp.x = 0.0f;
	vUp.y = 1.0f;
	vUp.z = 0.0f;
	vDir.x = 0.0f;
	vDir.y = 0.0f;
	vDir.z = 1.0f;
	qRot.x = 0.0f;
	qRot.y = 0.0f;
	qRot.z = 0.0f;
	qRot.w = 1.0f;
	mRot = mSca;

	// initialise position
	vPos.x = 0.0f;
	vPos.y = 0.0f;
	vPos.z = 0.0f;
	mPos = mSca;

	// ca c'est bon
	mMatrix = mSca;
}

void Transform::UpdateMatrix() {
	XMMATRIX matrix = XMLoadFloat4x4(&mSca);
	matrix *= XMLoadFloat4x4(&mRot);
	matrix *= XMLoadFloat4x4(&mPos);
	XMStoreFloat4x4(&mMatrix, matrix);
}

void Transform::Rotate(float yaw, float pitch, float roll) {

	// use GetDegreeToRadian(float fAngleDegree) to convert the angle
	XMVECTOR dir = XMLoadFloat3(&vDir);
	XMVECTOR right = XMLoadFloat3(&vRight);
	XMVECTOR up = XMLoadFloat3(&vUp);

	XMVECTOR  quat;
	XMVECTOR  quattemp;

	quattemp = XMQuaternionRotationAxis(dir, roll);
	quat = quattemp;

	quattemp = XMQuaternionRotationAxis(right, pitch);
	quat = XMQuaternionMultiply(quat, quattemp);

	quattemp = XMQuaternionRotationAxis(up, yaw);
	quat = XMQuaternionMultiply(quat, quattemp);

	quat = XMQuaternionMultiply(XMLoadFloat4(&qRot), quat);
	XMStoreFloat4(&qRot, quat);

	// Matrix
	XMStoreFloat4x4(&mRot, XMMatrixRotationQuaternion(quat));

	// Axis
	vRight.x = mRot._11;
	vRight.y = mRot._12;
	vRight.z = mRot._13;
	vUp.x = mRot._21;
	vUp.y = mRot._22;
	vUp.z = mRot._23;
	vDir.x = mRot._31;
	vDir.y = mRot._32;
	vDir.z = mRot._33;
}

void Transform::Translate(float X, float Y, float Z) {
	vPos.x += X;
	vPos.y += Y;
	vPos.z += Z;
	XMMATRIX m = XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
	XMStoreFloat4x4(&mPos, m) ;
}

void Transform::Scale(float X, float Y, float Z) {
	vSca.x += X;
	vSca.y += Y;
	vSca.z += Z;
	XMMATRIX m = XMMatrixScaling(vSca.x, vSca.y, vSca.z);
	XMStoreFloat4x4(&mSca, m);
}