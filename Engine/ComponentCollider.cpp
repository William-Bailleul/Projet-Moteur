#include "ComponentCollider.h"
#include "GameManager.h"
#include "GameObject.h"
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
	if (hitBoxes.size() > 0) {

		std::vector<GameObject*> currentObjectList = gameManager->objectList;
		for (int i = 0; i < currentObjectList.size(); i++) {

			GameObject* currentObject = currentObjectList[i];
			ComponentCollider* currentCollider = *currentObject->getComponent<ComponentCollider*>();
			ComponentScript* currentScript = *currentObject->getComponent<ComponentScript*>();

			if (ListCollisionCheck(hitBoxes, currentCollider->hitBoxes)
				|| ListCollisionCheck(hitBoxes, currentCollider->hitSpheres)
				|| ListCollisionCheck(hitBoxes, currentCollider->hitFrustums)
				|| ListCollisionCheck(hitSpheres, currentCollider->hitBoxes)
				|| ListCollisionCheck(hitSpheres, currentCollider->hitSpheres)
				|| ListCollisionCheck(hitSpheres, currentCollider->hitFrustums)
				|| ListCollisionCheck(hitFrustums, currentCollider->hitBoxes)
				|| ListCollisionCheck(hitFrustums, currentCollider->hitSpheres)
				|| ListCollisionCheck(hitFrustums, currentCollider->hitFrustums)) {
				objectScript->AddToQueue(currentScript->GetName());
			}
		}
	}
}

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
	collisionType = boundingOne->Contains(boundingTwo);
	return collisionType;
}



//add a new BoundingBox to the hitBoxes list
void ComponentCollider::NewHitBox(){
}

//add a new BoundingSphere to the hitBoxes list
void ComponentCollider::NewHitSphere(){
}

//add a new BoundingFrustum to the hitBoxes list
void ComponentCollider::NewHitFrustum(){
}

ComponentCollider::~ComponentCollider() {
	//use frees and deletes to remove all the contents of the lists etc
};
*/