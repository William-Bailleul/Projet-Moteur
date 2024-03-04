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
	template <typename U, typename V> bool ListCollisionCheck(std::vector<U*> listOne, std::vector<V*> listTwo);
	template <typename U, typename V> int OneCollisionCheck(U* Bounding, V* BoundingDos);

	//create functions
	void NewHitBox();
	void NewHitSphere();
	void NewHitFrustum();

private:
	void Init(GameManager* manager, ComponentScript* script);
};

