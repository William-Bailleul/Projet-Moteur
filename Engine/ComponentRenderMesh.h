#pragma once

#include "Component.h"
#include "Utile.h"
#include "GeometryHandler.h"

//struct Mesh;
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

	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT4 Color;
	};

	struct FrameResource
	{
	public:

		FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount);
		FrameResource(const FrameResource& rhs) = delete;
		FrameResource& operator=(const FrameResource& rhs) = delete;
		~FrameResource();

		// We cannot reset the allocator until the GPU is done processing the commands.
		// So each frame needs their own allocator.
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CmdListAlloc;

		// We cannot update a cbuffer until the GPU is done processing the commands
		// that reference it.  So each frame needs their own cbuffers.
		std::unique_ptr<UploadBuffer<PassConstants>> PassCB = nullptr;
		std::unique_ptr<UploadBuffer<ObjectConstants>> ObjectCB = nullptr;

		// Fence value to mark commands up to this fence point.  This lets us
		// check if these frame resources are still in use by the GPU.
		UINT64 Fence = 0;
	};

	GeometryHandler::GeometryHandler::Mesh refMesh;
	Shader* refShader;
	Texture* refTexture;

	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	std::vector<RenderItem*> mOpaqueRitems;
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;

	ComponentRenderMesh(GameObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	~ComponentRenderMesh();

private:
	void Init(GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	void BuildRenderItems();
	void DrawRenderItem(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

};

