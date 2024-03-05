#pragma once

#include "Component.h"

#include <vector>
#include <DirectXCollision.h>

using namespace DirectX;

class GameManager;
class ComponentScript;

class ComponentCollider : public Component
{
public:

	//linking to the object's script, necessary if we want to implement reactions to 
	ComponentScript* objectScript;

	//saving the GameManager's address to check its objectList
	GameManager* gameManager;

	// vectors can remain empty without issue
	std::vector<BoundingBox*> hitBoxes;
	std::vector<BoundingSphere*> hitSpheres;
	std::vector<BoundingFrustum*> hitFrustums;

	ComponentCollider(GameObject* gameObjectPointer, GameManager* manager, ComponentScript* script);
	~ComponentCollider();

	//check functions
	void FullCollisionCheck(); 

	template <typename U, typename V> bool ListCollisionCheck(std::vector<U*> listOne, std::vector<V*> listTwo) {
		for (int i = 0; i < listOne.size(); i++) {
			for (int j = 0; j < listTwo.size(); j++) {
				if (OneCollisionCheck(listOne[i], listTwo[j]) != 0) {
					return true;
				}
			}
		}
		return false;
	}

	template <typename U, typename V> int OneCollisionCheck(U* boundingOne, V* boundingTwo) {
		int collisionType;
		collisionType = boundingOne->Contains(boundingTwo);
		return collisionType;
	}

	//create functions
	void NewHitBox(XMFLOAT3& center, XMFLOAT3& extents);
	void NewHitSphere(XMFLOAT3& center, float radius);
	void NewHitFrustum(const XMFLOAT3& _Origin, const XMFLOAT4& _Orientation, float _RightSlope, float _LeftSlope, float _TopSlope, float _BottomSlope, float _Near, float _Far);

private:
	void Init(GameManager* manager, ComponentScript* script);
};

