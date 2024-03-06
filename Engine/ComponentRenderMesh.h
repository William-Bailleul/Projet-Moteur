#pragma once

#include "Component.h"
#include "Utile.h"
#include "GeometryHandler.h"

struct GeometryHandler::Mesh;
class Shader;
class Texture;

class ComponentRenderMesh : public Component
{
public:
	struct RenderItem
	{
		RenderItem() = default;

		//Matrice du Monde
		DirectX::XMFLOAT4X4 World = MathHelper::Identity4x4();

		const int gNumFrameResources = 3;
		int NumFramesDirty = gNumFrameResources;

		// Index into GPU constant buffer corresponding to the ObjectCB for this render item.
		UINT ObjCBIndex = -1;

		MeshGeometry* Geo = nullptr;

		// Primitive topology.
		D3D12_PRIMITIVE_TOPOLOGY PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		// DrawIndexedInstanced parameters.
		UINT IndexCount = 0;
		UINT StartIndexLocation = 0;
		int BaseVertexLocation = 0;
	};

	GeometryHandler::Mesh refMesh;
	Shader* refShader;
	Texture* refTexture;

	ComponentRenderMesh(GameObject* gameObjectPointer, GeometryHandler::Mesh* meshRef, Shader* shaderRef, Texture* textureRef);
	~ComponentRenderMesh();

private:
	void Init(GeometryHandler::Mesh* meshRef, Shader* shaderRef, Texture* textureRef);
	void DrawRenderItem(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

};

