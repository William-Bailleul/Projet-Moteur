#pragma once

#include "Component.h"
#include "Engine.h"
#include "GeometryHandler.h"

//struct Mesh;
class Shader;
struct Texture;

using namespace DirectX;

class ComponentRenderMesh : public Component
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};

	GeometryHandler::GeometryHandler::Mesh refMesh;
	Shader* refShader;
	Texture* refTexture;

	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	std::vector<std::unique_ptr<D3DApp::RenderItem>> mAllRitems;
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;

	UINT meshVertexOffset;
	UINT meshIndexOffset;
	UINT totalVertexCount;

	SubmeshGeometry meshSubmesh;

	ComponentRenderMesh();
	ComponentRenderMesh(EngineObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	~ComponentRenderMesh();

	void Init(EngineObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	

private:
	void Init(GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);


};

