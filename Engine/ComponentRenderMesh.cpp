#include "ComponentRenderMesh.h"

ComponentRenderMesh::ComponentRenderMesh(GameObject* gameObjectPointer, Mesh* meshRef, Shader* shaderRef, Texture* textureRef) :Component::Component(gameObjectPointer) {
	Init(meshRef, shaderRef, textureRef);
}

void ComponentRenderMesh::Init(Mesh* meshRef, Shader* shaderRef, Texture* textureRef) {
	refMesh = meshRef;
	refShader = shaderRef;
	refTexture = textureRef;
}

ComponentRenderMesh::~ComponentRenderMesh() {
}