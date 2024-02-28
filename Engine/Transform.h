#pragma once
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

#define PI 3.14159265358979323846264338327950288

using namespace DirectX;
using namespace DirectX::PackedVector;

class Transform
{
	//Scale
	XMFLOAT3 vSca;
	XMFLOAT3X3 mSca;

	//Rotate
	XMFLOAT3 vDir;
	XMFLOAT3 vRight;
	XMFLOAT3 vUp;
	XMFLOAT4 qRot;
	XMFLOAT4X4 mRot;
	
	//Position
	XMFLOAT3 vPos;
	XMFLOAT3X3 mPos;

	//Matrix of the object
	XMFLOAT3X3 mMatrix;

	void Identity();
	void FromMatrix(XMFLOAT3X3* pMat);
	void UpdateRotationFromVectors();
	void UpdateRotationFromQuaternion();
	void UpdateRotationFromMatrix();
	void UpdateMatrix();
	void Rotate(float yaw, float pitch, float roll);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateRoll(float angle);
	void RotateWorld(XMFLOAT3X3* pMatrix);
	void RotateWorldX(float angle);
	void RotateWorldY(float angle);
	void RotateWorldZ(float angle);
};

