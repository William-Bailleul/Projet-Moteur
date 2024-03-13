#pragma once

#include "Engine.h"
#include "GeometryHandler.h"
#include "ComponentRenderMesh.h"

class Renderer
{
	

public:

	Renderer();
	~Renderer();

	void BuildRenderItems();
	void DrawRenderItem(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, const std::vector<D3DApp::RenderItem*>& ritems, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap, UINT mCbvSrvUavDescriptorSize);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);
	void UpdateCaches(GeometryHandler::Mesh& meshRef);

	void CreateList();
	void AddList(ComponentRenderMesh* rMesh);
	void RemoveList(ComponentRenderMesh* rMesh);

public:
	std::vector<ComponentRenderMesh*> rItemList;
	std::unordered_map<std::string, MeshGeometry> mGeometries;
	int listTotal;

private:
	std::vector<D3DApp::RenderItem*> mOpaqueRitems;
	D3DApp::FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;
	UINT mCbvSrvUavDescriptorSize = 0;
};

