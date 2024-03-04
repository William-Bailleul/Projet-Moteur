#include "ComponentCollider.h"
#include "GameManager.h"
#include "GameObject.h"

#include <vector>

ComponentCollider::ComponentCollider(GameObject* gameObjectPointer, GameManager* manager) :Component::Component(gameObjectPointer) {
	Init(manager);
};

void ComponentCollider::Init(GameManager* manager) {
	gameManager = manager;
}

//checks for collisions
void ComponentCollider::FullCollisionCheck() {

	// sloppy mess code, gotta optimize this somehow
	// remember to parse the game's generated "field" in a grid to avoid checking the entire scene for collisions everytime 

	if (hitBoxes.size() > 0) {
		for (int i = 0; i < hitBoxes.size(); i++) {

			std::vector<GameObject*> currentObjectList = gameManager->objectList;
			for (int j = 0; j < currentObjectList.size(); j++) {

				GameObject* currentObject = currentObjectList[j];
				for (int k = 0; k < currentObject->componentList.size(); k++) {

					// if the current component is a collider
					// does the OG component list even accept non-"components" that inherit components 
					if (typeid(currentObject->componentList[k]) == typeid(ComponentCollider*)) {

						// now make it check all of its hitBoxes/Spheres/Frustums
						// with the Contains() and Intersects() functions

						//currentObject->componentList[k]->;
						
					}
				}
			}
		}
	}

	if (hitSpheres.size() > 0) {
		for (int i = 0; i < hitSpheres.size(); i++) {

		}
	}

	if (hitFrustums.size() > 0) {
		for (int i = 0; i < hitFrustums.size(); i++) {

		}
	}
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
