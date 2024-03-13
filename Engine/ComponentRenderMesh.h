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

	std::vector<D3DApp::RenderItem*> mOpaqueRitems;
	D3DApp::FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	std::vector<std::unique_ptr<D3DApp::RenderItem>> mAllRitems;
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;

	ComponentRenderMesh();
	ComponentRenderMesh(EngineObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	~ComponentRenderMesh();

	void Init(EngineObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	void BuildRenderItems();
	void DrawRenderItem(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, const std::vector<D3DApp::RenderItem*>& ritems, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap, UINT mCbvSrvUavDescriptorSize);


	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	UINT mPassCbvOffset = 0;

	bool mIsWireframe = false;

	XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };


	float mTheta = 1.5f * XM_PI;
	float mPhi = 0.2f * XM_PI;
	float mRadius = 15.0f;

	POINT mLastMousePos;

private:
	void Init(GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef);
	int mClientWidth = 800;
	int mClientHeight = 600;
};

