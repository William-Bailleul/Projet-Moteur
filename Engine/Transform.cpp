#include "Transform.h"

void Transform::Identity(float angle, float ScaX, float ScaY, float ScaZ, float PosX, float PosY, float PosZ) {
	// initialise scale
	vSca.x = ScaX;
	vSca.y = ScaY;
	vSca.z = ScaZ;
	vSca.w = 1;
	XMVECTOR vScale = XMLoadFloat4(&vSca);
	XMMATRIX scale = XMMatrixScalingFromVector(vScale);
	XMStoreFloat4x4(&mSca, scale);

	// initialise rotation
	vRight.x = cos(angle);
	vRight.y = sin(angle);
	vRight.z = 0;
	vUp.x = 0;
	vUp.y = cos(angle);
	vUp.z = sin(angle);
	vRoll.x = cos(angle);
	vRoll.y = 0;
	vRoll.z = -sin(angle);

	// initialise position
	vPos.x = PosX;
	vPos.y = PosY;
	vPos.z = PosZ;
	mPos._11 = PosX;
	mPos._22 = PosY;
	mPos._33 = PosZ;
	mPos._44 = 1;

	//initialise matrix of the object
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

void Transform::UpdateMatrix() {
	XMMATRIX matrix = XMLoadFloat4x4(&mSca);
	matrix *= XMLoadFloat4x4(&mRot);
	matrix *= XMLoadFloat4x4(&mPos);
	XMStoreFloat4x4(&mMatrix, matrix);
}

void Transform::Rotate(float yaw, float pitch, float roll) {
	// use GetDegreeToRadian(float fAngleDegree) to convert the angle
	XMVECTOR dir = XMVector3Normalize(XMLoadFloat3(&vDir));
	XMVECTOR right = XMVector3Normalize(XMLoadFloat3(&vRight));
	XMVECTOR up = XMVector3Normalize(XMLoadFloat3(&vUp));

	XMVECTOR  quat;
	XMVECTOR  quattemp;

	quattemp = XMQuaternionRotationAxis(dir, roll);
	quat = XMQuaternionMultiply(XMLoadFloat4(&qRot) ,quattemp);
	XMStoreFloat4(&qRot, quat);

	quattemp = XMQuaternionRotationAxis(right, pitch);
	quat = XMQuaternionMultiply(XMLoadFloat4(&qRot), quattemp);
	XMStoreFloat4(&qRot, quat);

	quattemp = XMQuaternionRotationAxis(up, yaw);
	quat = XMQuaternionMultiply(XMLoadFloat4(&qRot), quattemp);
	XMStoreFloat4(&qRot, quat);

	XMStoreFloat4x4(&mRot, XMMatrixRotationQuaternion(XMLoadFloat4(&qRot)));

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
