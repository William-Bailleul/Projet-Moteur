#include "ComponentCollider.h"

ComponentCollider::ComponentCollider(GameObject* gameObjectPointer, BoundaryStyle boundaryStyle) :Component::Component(gameObjectPointer) {
	Init(boundaryStyle);
};

void ComponentCollider::Init(BoundaryStyle boundaryStyle) {
	switch (boundaryStyle) {
	case RECT:

		break;
	case BOX:

		break;
	case SPHERE:

		break;

	default:
		break;
	}
}

ComponentCollider::~ComponentCollider() {
	//use frees and deletes to remove all the contents of the lists etc
};
