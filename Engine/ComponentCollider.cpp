#include "ComponentCollider.h"
#include "EngineManager.h"
#include "EngineObject.h"
#include "ComponentScript.h"

#include <vector>
/*
ComponentCollider::ComponentCollider(GameObject* gameObjectPointer, GameManager* manager, ComponentScript* script) :Component::Component(gameObjectPointer) {
	Init(manager, script);
};

void ComponentCollider::Init(GameManager* manager, ComponentScript* script) {
	gameManager = manager;
	objectScript = script;
}

//checks for collisions
void ComponentCollider::FullCollisionCheck() {

	// remember to parse the game's generated "field" in a grid to avoid checking the entire scene for collisions everytime 
	if (hitBoxes.size() > 0 || hitSpheres.size() > 0 || hitBoxes.size() > 0) {

		std::vector<GameObject*> currentObjectList = gameManager->objectList;
		for (int i = 0; i < currentObjectList.size(); i++) {
			GameObject* currentObject = currentObjectList[i];
			
			if (currentObject != gameObjectPointer) {

				ComponentCollider* currentCollider = currentObject->getComponent<ComponentCollider>();
				ComponentScript* currentScript = currentObject->getComponent<ComponentScript>();

				//if there is any collision between this object and another
				if (ListCollisionCheck(hitBoxes, currentCollider->hitBoxes)
					|| ListCollisionCheck(hitBoxes, currentCollider->hitSpheres)
					|| ListCollisionCheck(hitBoxes, currentCollider->hitFrustums)
					|| ListCollisionCheck(hitSpheres, currentCollider->hitBoxes)
					|| ListCollisionCheck(hitSpheres, currentCollider->hitSpheres)
					|| ListCollisionCheck(hitSpheres, currentCollider->hitFrustums)
					|| ListCollisionCheck(hitFrustums, currentCollider->hitBoxes)
					|| ListCollisionCheck(hitFrustums, currentCollider->hitSpheres)
					|| ListCollisionCheck(hitFrustums, currentCollider->hitFrustums)) {
					//retrieve the other object's name and add it to the script queue for processing
					objectScript->AddToQueue(currentScript->GetName());
				}
			}
		}
	}
}

//add a new BoundingBox to the hitBoxes list
void ComponentCollider::NewHitBox(XMFLOAT3& center, XMFLOAT3& extents){
	hitBoxes.push_back(new BoundingBox(center, extents));
}

//add a new BoundingSphere to the hitBoxes list
void ComponentCollider::NewHitSphere(XMFLOAT3& center, float radius){
	hitSpheres.push_back(new BoundingSphere(center, radius));
}

//add a new BoundingFrustum to the hitBoxes list
void ComponentCollider::NewHitFrustum(const XMFLOAT3& _Origin, const XMFLOAT4& _Orientation, float _RightSlope, float _LeftSlope, float _TopSlope, float _BottomSlope, float _Near, float _Far){
	hitFrustums.push_back(new BoundingFrustum());
}

ComponentCollider::~ComponentCollider() {
	//use frees and deletes to remove all the contents of the lists etc
	for (int i = 0; i < hitBoxes.size(); i++) {
		delete (hitBoxes[0]);
	}
	for (int i = 0; i < hitFrustums.size(); i++) {
		delete (hitFrustums[0]);
	}
	for (int i = 0; i < hitSpheres.size(); i++) {
		delete (hitSpheres[0]);
	}
};
