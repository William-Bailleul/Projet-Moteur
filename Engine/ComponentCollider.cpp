#include "ComponentCollider.h"
#include "EngineManager.h"
#include "EngineObject.h"


ComponentCollider::ComponentCollider(EngineObject* gameObjectPointer, EngineManager* manager, ComponentScript* script) :Component::Component(gameObjectPointer) {
	Init(manager, script);
};

void ComponentCollider::Init(EngineManager* manager, ComponentScript* script) {
	gameManager = manager;
	objectScript = script;
}

//checks for collisions
void ComponentCollider::FullCollisionCheck() {

	std::vector<std::string> thisLoopHitNames;
	// remember to parse the game's generated "field" in a grid to avoid checking the entire scene for collisions everytime 
	if (hitBoxes.size() > 0 || hitSpheres.size() > 0 || hitBoxes.size() > 0) {


		std::vector<EngineObject*> currentObjectList = gameManager->objectList;
		for (int i = 0; i < currentObjectList.size(); i++) {
			EngineObject* currentObject = currentObjectList[i];
			
			if (currentObject != gameObjectPointer) {

				ComponentCollider* currentCollider = currentObject->getComponent<ComponentCollider>();

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
					//retrieve the other object's name and add it to the name list
					thisLoopHitNames.push_back(currentCollider->nameTag);
				}
			}
		}
	}

	//then we remove the names we haven't kept between currentHitNames and thisLoopHitNames
	size_t vecSize = currentHitNames.size();
	int index = 0;

	while (index < vecSize) {
		//if a name in currentHitNames isnt in thisLoopHitNames as well
		if (std::count(thisLoopHitNames.begin(), thisLoopHitNames.end(), currentHitNames[index]) == 0) {
			currentHitNames.erase((std::remove(currentHitNames.begin(), currentHitNames.end(), thisLoopHitNames[index]), currentHitNames.end()));
			vecSize--;
		}
		else {
			index++;
		}
	}

	//and add the new ones in
	for (int i = 0; i < thisLoopHitNames.size(); i++) {
		//if it's not in already
		if (std::count(currentHitNames.begin(), currentHitNames.end(), thisLoopHitNames[i]) == 0) {
			currentHitNames.push_back(thisLoopHitNames[i]);
		}
	}
}

void ComponentCollider::SaveToPrevious() {
	
	//emptying the previous collision list
	for (int i = 0; i < previousHitNames.size(); i++) {
		previousHitNames.erase(previousHitNames.begin());
	}
	//refilling it again with the current data before updating
	for (int i = 0; i < currentHitNames.size(); i++) {
		previousHitNames.push_back(currentHitNames[i]);
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