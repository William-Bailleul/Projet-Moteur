#pragma once

#include "Component.h"
#include "Utile.h"
#include "Engine.h"
#include "GeometryHandler.h"

//struct Mesh;
class Shader;
struct Texture;

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

	std::vector<D3DApp::RenderItem*> mOpaqueRitems;
	D3DApp::FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	std::vector<std::unique_ptr<D3DApp::RenderItem>> mAllRitems;
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;

	ComponentRenderMesh(GameObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	~ComponentRenderMesh();

private:
	void Init(GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	void BuildRenderItems();
	void DrawRenderItem(ID3D12GraphicsCommandList* cmdList, const std::vector<D3DApp::RenderItem*>& ritems, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap, UINT mCbvSrvUavDescriptorSize);

};

