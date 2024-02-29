#pragma once

#include "Component.h"

struct Mesh;
class Shader;
class Texture;

class ComponentRenderMesh : public Component
{
	Mesh* refMesh;
	Shader* refShader;
	Texture* refTexture;

	ComponentRenderMesh(GameObject* gameObjectPointer, Mesh* meshRef, Shader* shaderRef, Texture* textureRef);
	~ComponentRenderMesh();

private:
	void Init(Mesh* meshRef, Shader* shaderRef, Texture* textureRef);
};

