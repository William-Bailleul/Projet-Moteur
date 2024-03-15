#pragma once

#include "Utile.h"

#define PI 3.14159265358979323846264338327950288

using namespace DirectX;
using namespace DirectX::PackedVector;

struct Transform
{
	//Scale
	XMFLOAT3 vSca;
	XMFLOAT4X4 mSca;

	//Rotate
	XMFLOAT3 vDir;
	XMFLOAT3 vRight;
	XMFLOAT3 vUp;
	XMFLOAT4 qRot;
	XMFLOAT4X4 mRot;

	//Position
	XMFLOAT3 vPos;
	XMFLOAT4X4 mPos;

	//Matrix of the object
	XMFLOAT4X4 mMatrix;

	Transform();
	void Identity();
	void UpdateMatrix();
	void Rotate(float yaw, float pitch, float roll);
	void Translate(float X, float Y, float Z);
	void Scale(float X, float Y, float Z);
};

