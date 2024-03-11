#pragma once

#include "Engine.h"
#include "GeometryHandler.h"

class Renderer
{
	Renderer();

public:
	void BuildRenderItems();
	void DrawRenderItem(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, const std::vector<D3DApp::RenderItem*>& ritems, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap, UINT mCbvSrvUavDescriptorSize);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);
	void UpdateCaches(GeometryHandler::Mesh& meshRef);

public:
	std::vector<std::unique_ptr<D3DApp::RenderItem>> mAllRitems;
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;

private:
	std::vector<D3DApp::RenderItem*> mOpaqueRitems;
	D3DApp::FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;
	UINT mCbvSrvUavDescriptorSize = 0;
};

