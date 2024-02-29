#pragma once
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include<vector>

#define PI 3.14159265358979323846264338327950288

using namespace DirectX;
using namespace DirectX::PackedVector;

class Component;

class GameObject
{
	struct Transform
	{
		//Scale
		XMFLOAT4 vSca;
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

		void Identity();
		void FromMatrix(XMFLOAT4X4* pMat);
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
		void Scale(float x, float y, float z);
		void SetPosition(int x, int y, int z);
	};
public:
	std::vector<Component*> componentList;

	GameObject();
	~GameObject();
	void addComponent(Component* component);
};