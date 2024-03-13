#pragma once

#include "Component.h"

#include <vector>
#include <string>
#include <DirectXCollision.h>

using namespace DirectX;

class EngineManager;
class ComponentScript;

class ComponentCollider : public Component
{
public:

	//linking to the object's script, necessary if we want to implement reactions to 
	ComponentScript* objectScript;
	std::string nameTag;

	//saving the GameManager's address to check its objectList
	EngineManager* gameManager;

	std::vector<std::string> currentHitNames;
	std::vector<std::string> previousHitNames;

	// vectors can remain empty without issue
	std::vector<BoundingBox*> hitBoxes;
	std::vector<BoundingSphere*> hitSpheres;
	std::vector<BoundingFrustum*> hitFrustums;

	ComponentCollider(EngineObject* gameObjectPointer, EngineManager* manager, ComponentScript* script);
	~ComponentCollider();

	//check functions
	void FullCollisionCheck(); 
	void SaveToPrevious();
	template  <typename U, typename V> bool ListCollisionCheck(std::vector<U*> listOne, std::vector<V*> listTwo);
	template <typename U, typename V> int OneCollisionCheck(U* boundingOne, V* boundingTwo);

	//create functions
	void NewHitBox(XMFLOAT3& center, XMFLOAT3& extents);
	void NewHitSphere(XMFLOAT3& center, float radius);
	void NewHitFrustum(const XMFLOAT3& _Origin, const XMFLOAT4& _Orientation, float _RightSlope, float _LeftSlope, float _TopSlope, float _BottomSlope, float _Near, float _Far);

private:
	void Init(EngineManager* manager, ComponentScript* script);
};

template <typename U, typename V> bool ComponentCollider::ListCollisionCheck(std::vector<U*> listOne, std::vector<V*> listTwo) {
	for (int i = 0; i < listOne.size(); i++) {
		for (int j = 0; j < listTwo.size(); j++) {
			if (OneCollisionCheck(listOne[i], listTwo[j]) != 0) {
				return true;
			}
		}
	}
	return false;
}

template <typename U, typename V> int ComponentCollider::OneCollisionCheck(U* boundingOne, V* boundingTwo) {
	int collisionType;
	collisionType = boundingOne->Contains(*boundingTwo);
	return collisionType;
}