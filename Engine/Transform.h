#pragma once

#include "Utile.h"

#define PI 3.14159265358979323846264338327950288

using namespace DirectX;
using namespace DirectX::PackedVector;

struct Transform
{
	//Scale
	XMFLOAT4 vSca;
	XMFLOAT4X4 mSca;

	//Rotate
	XMFLOAT3 vDir;
	XMFLOAT3 vRight;
	XMFLOAT3 vUp;
	XMFLOAT3 vRoll;
	XMFLOAT4 qRot;
	XMFLOAT4X4 mRot;

	//Position
	XMFLOAT3 vPos;
	XMFLOAT4X4 mPos;

	//Matrix of the object
	XMFLOAT4X4 mMatrix;

	void Identity(float angle, float ScaX, float ScaY, float ScaZ, float PosX, float PosY, float PosZ);
	void UpdateMatrix();
	void Rotate(float yaw, float pitch, float roll);
};

