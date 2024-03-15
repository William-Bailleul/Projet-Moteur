#include "Engine.h"
#include "Utile.h"
#include "Shader.h"
#include "EngineObject.h"
#include "EngineManager.h"
#include "ComponentRenderMesh.h"
#include "InputController.h"
#include "ComponentCamera.h"
#include "Transform.h"
#include <DirectXColors.h>
#include "EngineTimer.h"

using namespace DirectX;

struct PassConstants
{
	XMFLOAT4X4 View = MathHelper::Identity4x4();
	XMFLOAT4X4 Proj = MathHelper::Identity4x4();
};

class InitDirect3DApp : public D3DApp
{
public:
	InitDirect3DApp(HINSTANCE hInstance);
	~InitDirect3DApp();

	virtual bool Initialize()override;
	void DrawEdit(const GameTimer& gt, ComponentRenderMesh& oRMesh);

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);

	Camera camera;
	InputManager input;
	Transform transform;


private:
	virtual void OnResize()override;
	virtual void Update(GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;
	void UpdateCamera(GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);


	Shader oShader;
	Texture oTexture;
	EngineManager testManager;
	GeometryHandler oMeshH;
	GeometryHandler::Mesh oMesh;
	ComponentRenderMesh oRMesh;

	std::vector<RenderItem*> mAllRitems;
	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>> mPSOs;
	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

	PassConstants mMainPassCB;

	UINT mPassCbvOffset = 0;

	bool mIsWireframe = false;

	XMFLOAT3 mVectStart = { 0.0f,0.0f,-8.0f };
	XMFLOAT3 mEyePos = { 0.0f, 0.0f, 0.0f };

	float mTheta = 1.5f * XM_PI;
	float mPhi = 0.2f * XM_PI;
	float mRadius = 15.0f;


	POINT mLastMousePos;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		InitDirect3DApp theApp(hInstance);
		if (!theApp.Initialize())
			return 0;

		return theApp.Run();
	}
	catch (DxException& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		return 0;
	}
}

InitDirect3DApp::InitDirect3DApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
}

InitDirect3DApp::~InitDirect3DApp()
{
}

bool InitDirect3DApp::Initialize()
{
	#if defined(DEBUG) || defined(_DEBUG) // Enable the D3D12 debug layer.
		{
			ID3D12Debug* debugController;
			if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
				return false;
			}
			debugController->EnableDebugLayer();
			debugController->Release();
		}
	#endif
	if (!D3DApp::Initialize())
		return false;

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	//BUILD ROOT SIGNATURES


	CD3DX12_DESCRIPTOR_RANGE cbvTable0;
	cbvTable0.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);

	CD3DX12_DESCRIPTOR_RANGE cbvTable1;
	cbvTable1.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 1);

	// Root parameter can be a table, root descriptor or root constants.
	CD3DX12_ROOT_PARAMETER slotRootParameter[2];

	// Create root CBVs.
	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable0);
	slotRootParameter[1].InitAsDescriptorTable(1, &cbvTable1);

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(2, slotRootParameter, 0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(mRootSignature.GetAddressOf())));



	//Camera Start Position
	camera.SetPosition(mVectStart);

	//INIT

	const char* entrypoint = "VS";
	const char* target = "vs_5_1";
	const char* entrypoint2 = "PS";
	const char* target2 = "ps_5_1";

	mShaders["VS"] = Utile::CompileShader(L"color.hlsl", nullptr, "VS", "vs_5_1");
	mShaders["PS"] = Utile::CompileShader(L"color.hlsl", nullptr, "PS", "ps_5_1");

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};


	//CREATION DE BOITE + GEOSPHERE

	GeometryHandler meshObject;
	GeometryHandler::Mesh box = meshObject.BuildBox(1.f, 1.f, 1.f , 1);
	GeometryHandler::Mesh sphere = meshObject.BuildSphere(3.0f, 20, 20);
	GeometryHandler::Mesh cylinder = meshObject.BuildCylinder(3.0f, 3.0f, 5.0f, 20,20);
	GeometryHandler::Mesh geosphere = meshObject.BuildGeosphere(2.5f, 5);
	GeometryHandler::Mesh enemy = meshObject.BuildPyramid(5.0f, 3);
	GeometryHandler::Mesh worldBox = meshObject.BuildBox(1.f, 1.f, 1.f , 10, 1);


	//VERTEX OFFSET
	UINT boxVertexOffset = 0;
	UINT sphereVertexOffset = boxVertexOffset + (UINT)box.Vertices.size();
	UINT cylinderVertexOffset = sphereVertexOffset + (UINT)sphere.Vertices.size();
	UINT geosphereVertexOffset = cylinderVertexOffset + (UINT)cylinder.Vertices.size();
	UINT enemyVertexOffset = geosphereVertexOffset + (UINT)geosphere.Vertices.size();
	UINT worldBoxVertexOffset = enemyVertexOffset + (UINT)enemy.Vertices.size();

	//INDEX OFFSET

	UINT boxIndexOffset = 0;
	UINT gridIndexOffset = (UINT)box.Indices32.size();
	UINT sphereIndexOffset = boxIndexOffset + (UINT)box.Indices32.size();
	UINT cylinderIndexOffset = sphereIndexOffset + (UINT)sphere.Indices32.size();
	UINT geosphereIndexOffset = cylinderIndexOffset + (UINT)cylinder.Indices32.size();
	UINT enemyIndexOffset = geosphereIndexOffset + (UINT)geosphere.Indices32.size();
	UINT worldBoxIndexOffset =enemyIndexOffset + (UINT)enemy.Indices32.size();


	//SUBMESH GEOMETRY

	SubmeshGeometry boxSubmesh;
	boxSubmesh.IndexCount = (UINT)box.Indices32.size();
	boxSubmesh.StartIndexLocation = boxIndexOffset;
	boxSubmesh.BaseVertexLocation = boxVertexOffset;

	SubmeshGeometry sphereSubmesh;
	sphereSubmesh.IndexCount = (UINT)sphere.Indices32.size();
	sphereSubmesh.StartIndexLocation = sphereIndexOffset;
	sphereSubmesh.BaseVertexLocation = sphereVertexOffset;
	
	SubmeshGeometry cylinderSubmesh;
	cylinderSubmesh.IndexCount = (UINT)cylinder.Indices32.size();
	cylinderSubmesh.StartIndexLocation = cylinderIndexOffset;
	cylinderSubmesh.BaseVertexLocation = cylinderVertexOffset;
	
	SubmeshGeometry geosphereSubmesh;
	geosphereSubmesh.IndexCount = (UINT)geosphere.Indices32.size();
	geosphereSubmesh.StartIndexLocation = geosphereIndexOffset;
	geosphereSubmesh.BaseVertexLocation = geosphereVertexOffset;

	SubmeshGeometry enemySubmesh;
	enemySubmesh.IndexCount = (UINT)enemy.Indices32.size();
	enemySubmesh.StartIndexLocation = enemyIndexOffset;
	enemySubmesh.BaseVertexLocation = enemyVertexOffset;

	SubmeshGeometry worldBoxSubmesh;
	worldBoxSubmesh.IndexCount = (UINT)worldBox.Indices32.size();
	worldBoxSubmesh.StartIndexLocation = worldBoxIndexOffset;
	worldBoxSubmesh.BaseVertexLocation = worldBoxVertexOffset;

	//VERTEX COUNT

	auto totalVertexCount =
		box.Vertices.size() +
		sphere.Vertices.size() +
		cylinder.Vertices.size() +
		geosphere.Vertices.size() +
		enemy.Vertices.size() +
		worldBox.Vertices.size();


	//SET POS + COLOR

	std::vector<ComponentRenderMesh::Vertex> vertices(totalVertexCount);

	UINT k = 0;
	for (size_t i = 0; i < box.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = box.Vertices[i].Position;
		vertices[k].Color = XMFLOAT4(DirectX::Colors::Cyan);
	}

	for (size_t i = 0; i < sphere.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = sphere.Vertices[i].Position;
		vertices[k].Color = XMFLOAT4(DirectX::Colors::Crimson);
	}

	for (size_t i = 0; i < cylinder.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = cylinder.Vertices[i].Position;
		vertices[k].Color = XMFLOAT4(DirectX::Colors::SteelBlue);
	}

	for (size_t i = 0; i < geosphere.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = geosphere.Vertices[i].Position;
		vertices[k].Color = XMFLOAT4(DirectX::Colors::Cyan);
	}

	for (size_t i = 0; i < enemy.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = enemy.Vertices[i].Position;
		vertices[k].Color = XMFLOAT4(DirectX::Colors::MintCream);
	}

	for (size_t i = 0; i < worldBox.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = worldBox.Vertices[i].Position;
		vertices[k].Color = XMFLOAT4(DirectX::Colors::PaleVioletRed);
	}


	//INSERT INDICES

	std::vector<std::uint16_t> indices;
	indices.insert(indices.end(), std::begin(box.GetIndices16()), std::end(box.GetIndices16()));
	indices.insert(indices.end(), std::begin(sphere.GetIndices16()), std::end(sphere.GetIndices16()));
	indices.insert(indices.end(), std::begin(cylinder.GetIndices16()), std::end(cylinder.GetIndices16()));
	indices.insert(indices.end(), std::begin(geosphere.GetIndices16()), std::end(geosphere.GetIndices16()));
	indices.insert(indices.end(), std::begin(enemy.GetIndices16()), std::end(enemy.GetIndices16()));
	indices.insert(indices.end(), std::begin(worldBox.GetIndices16()), std::end(worldBox.GetIndices16()));

	const UINT vbByteSize = (UINT)vertices.size() * sizeof(ComponentRenderMesh::Vertex);
	const UINT ibByteSize = (UINT)indices.size() * sizeof(std::uint16_t);



	//GEO

	auto geo = new MeshGeometry;
	geo->Name = "shapeGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &geo->VertexBufferCPU));
	CopyMemory(geo->VertexBufferCPU->GetBufferPointer(), vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &geo->IndexBufferCPU));
	CopyMemory(geo->IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);

	geo->VertexBufferGPU = Utile::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), vertices.data(), vbByteSize, geo->VertexBufferUploader);

	geo->IndexBufferGPU = Utile::CreateDefaultBuffer(md3dDevice.Get(),
		mCommandList.Get(), indices.data(), ibByteSize, geo->IndexBufferUploader);

	geo->VertexByteStride = sizeof(ComponentRenderMesh::Vertex);
	geo->VertexBufferByteSize = vbByteSize;
	geo->IndexFormat = DXGI_FORMAT_R16_UINT;
	geo->IndexBufferByteSize = ibByteSize;

	geo->DrawArgs["box"] = boxSubmesh;
	geo->DrawArgs["sphere"] = sphereSubmesh;
	geo->DrawArgs["cylinder"] = cylinderSubmesh;
	geo->DrawArgs["geosphere"] = geosphereSubmesh;
	geo->DrawArgs["enemy"] = enemySubmesh;
	geo->DrawArgs["worldBox"] = worldBoxSubmesh;

	std::unordered_map<std::string, MeshGeometry*> mGeometries;
	mGeometries[geo->Name] = geo;

	//BUILDRENDERITEMS
	UINT objCBIndex = -1;
	RenderItem* boxWorld = new RenderItem;
	XMMATRIX boxWorldWorld = XMMatrixTranslation(0.0f, 0.0f, 0.0f) * XMMatrixScaling(1000.f, 1000.f, 1000.f);
	XMStoreFloat4x4(&boxWorld->World, boxWorldWorld);
	boxWorld->ObjCBIndex++;
	boxWorld->Geo = mGeometries["shapeGeo"];
	boxWorld->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	boxWorld->IndexCount = boxWorld->Geo->DrawArgs["worldBox"].IndexCount;
	boxWorld->StartIndexLocation = boxWorld->Geo->DrawArgs["worldBox"].StartIndexLocation;
	boxWorld->BaseVertexLocation = boxWorld->Geo->DrawArgs["worldBox"].BaseVertexLocation;
	mAllRitems.push_back(boxWorld);


	// All the render items are opaque.
	for (auto& e : mAllRitems)
		mOpaqueRitems.push_back(e);


	//FRAME RESOURCES

	for (int i = 0; i < gNumFrameResources; ++i)
	{
		mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
			1, (UINT)mAllRitems.size()));
	}


	//DESCRIPTOR HEAPS

	UINT objCount = (UINT)mOpaqueRitems.size();

	// Need a CBV descriptor for each object for each frame resource,
	// +1 for the perPass CBV for each frame resource.
	UINT numDescriptors = (objCount + 1) * gNumFrameResources;

	// Save an offset to the start of the pass CBVs.  These are the last 3 descriptors.
	mPassCbvOffset = objCount * gNumFrameResources;

	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = numDescriptors;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&cbvHeapDesc,
		IID_PPV_ARGS(&mCbvHeap)));


	//CONSTANT BUFFER VIEWS

	UINT objCBByteSize = Utile::CalcConstantBufferByteSize(sizeof(ObjectConstants));

	// Need a CBV descriptor for each object for each frame resource.
	for (int frameIndex = 0; frameIndex < gNumFrameResources; ++frameIndex)
	{
		auto objectCB = mFrameResources[frameIndex]->ObjectCB->Resource();
		for (UINT i = 0; i < objCount; ++i)
		{
			D3D12_GPU_VIRTUAL_ADDRESS cbAddress = objectCB->GetGPUVirtualAddress();

			// Offset to the ith object constant buffer in the buffer.
			cbAddress += i * objCBByteSize;

			// Offset to the object cbv in the descriptor heap.
			int heapIndex = frameIndex * objCount + i;
			auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
			handle.Offset(heapIndex, mCbvSrvUavDescriptorSize);

			D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
			cbvDesc.BufferLocation = cbAddress;
			cbvDesc.SizeInBytes = objCBByteSize;

			md3dDevice->CreateConstantBufferView(&cbvDesc, handle);
		}
	}

	UINT passCBByteSize = Utile::CalcConstantBufferByteSize(sizeof(PassConstants));

	// Last three descriptors are the pass CBVs for each frame resource.
	for (int frameIndex = 0; frameIndex < gNumFrameResources; ++frameIndex)
	{
		auto passCB = mFrameResources[frameIndex]->PassCB->Resource();
		D3D12_GPU_VIRTUAL_ADDRESS cbAddress = passCB->GetGPUVirtualAddress();

		// Offset to the pass cbv in the descriptor heap.
		int heapIndex = mPassCbvOffset + frameIndex;
		auto handle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
		handle.Offset(heapIndex, mCbvSrvUavDescriptorSize);

		D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
		cbvDesc.BufferLocation = cbAddress;
		cbvDesc.SizeInBytes = passCBByteSize;

		md3dDevice->CreateConstantBufferView(&cbvDesc, handle);
	}


	//PSOs


	//
	// PSO for opaque objects.
	//
	ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	opaquePsoDesc.pRootSignature = mRootSignature.Get();
	opaquePsoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mShaders["VS"]->GetBufferPointer()),
		mShaders["VS"]->GetBufferSize()
	};
	opaquePsoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mShaders["PS"]->GetBufferPointer()),
		mShaders["PS"]->GetBufferSize()
	};
	opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	opaquePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	opaquePsoDesc.SampleMask = UINT_MAX;
	opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	opaquePsoDesc.NumRenderTargets = 1;
	opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
	opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	opaquePsoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mPSOs["opaque"])));


	//
	// PSO for opaque wireframe objects.
	//

	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaqueWireframePsoDesc = opaquePsoDesc;
	opaqueWireframePsoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaqueWireframePsoDesc, IID_PPV_ARGS(&mPSOs["opaque_wireframe"])));


	//END

	// Execute the initialization commands.
	ThrowIfFailed(mCommandList->Close());
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	FlushCommandQueue();

	return true;
}

void InitDirect3DApp::OnResize()
{
	D3DApp::OnResize();
}

void InitDirect3DApp::Update( GameTimer& gt)
{
	
	input.keyList();
	UpdateCamera(gt);

	// Cycle through the circular frame resource array.
	mCurrFrameResourceIndex = (mCurrFrameResourceIndex + 1) % gNumFrameResources;
	mCurrFrameResource = mFrameResources[mCurrFrameResourceIndex].get();

	// Has the GPU finished processing the commands of the current frame resource?
	// If not, wait until the GPU has completed commands up to this fence point.
	if (mCurrFrameResource->Fence != 0 && mFence->GetCompletedValue() < mCurrFrameResource->Fence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, L"false", false, EVENT_ALL_ACCESS);
		ThrowIfFailed(mFence->SetEventOnCompletion(mCurrFrameResource->Fence, eventHandle));
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}

	UpdateObjectCBs(gt);

	// Build the view matrix.
	XMVECTOR target = camera.GetPosition() + camera.GetLook();
	//target = XMVectorSet(0, 0, 0, 0);
	XMVECTOR cam = camera.GetPosition();
	//cam = XMVectorSet(0, 0, -10, 0);
	XMMATRIX view = XMMatrixLookAtLH(cam, target, camera.GetUp());
	XMStoreFloat4x4(&camera.mView, view);
	XMMATRIX proj = XMLoadFloat4x4(&camera.mProj);



	auto currPassCB = mCurrFrameResource->PassCB.get();
	
	XMFLOAT4X4 refView = MathHelper::Identity4x4();
	XMStoreFloat4x4(&refView, view);
	XMStoreFloat4x4(&camera.mProj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&camera.mView, XMMatrixTranspose(view));

	mMainPassCB.Proj = camera.mProj;
	mMainPassCB.View = camera.mView;
	currPassCB->CopyData(0, mMainPassCB);

}

void InitDirect3DApp::UpdateCamera(GameTimer& gt)
{

	float dt = gt.DeltaTime()*10;
	float walkSpeed = 2.0f;
	float speed = 0.2f;

	if (input.getKey(escape)) {
	}
	if (input.getKey(shoot)) {
	}
	
	if (input.getKey(accelerate)) {
		if (input.getKey(boost)) {
			camera.Walk(2 * (walkSpeed * dt));
		}
		camera.Walk(walkSpeed * dt);
	}
	if (input.getKey(backwards)) {
		camera.Walk(-walkSpeed * dt);
	}
	if (input.getKey(pitchDown)) {
		camera.Pitch(-dt * speed);
	}
	if (input.getKey(pitchUp)) {
		camera.Pitch(dt * speed);
	}
	if (input.getKey(yawLeft)) {
		camera.Strafe(-dt * speed);
	}
	if (input.getKey(yawRight)) {
		camera.Strafe(dt * speed);
	}
	if (input.getKey(rollLeft)) {
		camera.RotateY(-dt * speed);
	}	
	if (input.getKey(rollRight)) {
		camera.RotateY(dt * speed);
	}
}


void InitDirect3DApp::UpdateObjectCBs(const GameTimer& gt)
{
	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
	for (auto& e : mAllRitems)
	{
		// Only update the cbuffer data if the constants have changed.  
		// This needs to be tracked per frame resource.
		if (e->NumFramesDirty > 0)
		{
			DirectX::XMMATRIX world = XMLoadFloat4x4(&e->World);

			D3DApp::ObjectConstants objConstants;
			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));

			currObjectCB->CopyData(e->ObjCBIndex, objConstants);

			// Next FrameResource need to be updated too.
			e->NumFramesDirty--;
		}
	}
}

void InitDirect3DApp::Draw(const GameTimer& gt)
{

	auto cmdListAlloc = mCurrFrameResource->CmdListAlloc;

	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(cmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	
	if (mIsWireframe)
	{
		ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mPSOs["opaque_wireframe"].Get()));
	}
	else
	{
	ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mPSOs["opaque"].Get()));
	}
	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	// Indicate a state transition on the resource usage.
	CD3DX12_RESOURCE_BARRIER titi = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	mCommandList->ResourceBarrier(1, &titi);

	// Clear the back buffer and depth buffer.
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::Black, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE tata = CurrentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE toto = DepthStencilView();
	mCommandList->OMSetRenderTargets(1, &tata, true, &toto);

	ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap.Get() };
	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	mCommandList->SetGraphicsRootSignature(mRootSignature.Get());

	int passCbvIndex = mPassCbvOffset + mCurrFrameResourceIndex;
	auto passCbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
	passCbvHandle.Offset(passCbvIndex, mCbvSrvUavDescriptorSize);
	mCommandList->SetGraphicsRootDescriptorTable(1, passCbvHandle);

	DrawRenderItems(mCommandList.Get(), mOpaqueRitems);

	// Indicate a state transition on the resource usage.
	CD3DX12_RESOURCE_BARRIER tete = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	mCommandList->ResourceBarrier(1, &tete);

	// Done recording commands.
	ThrowIfFailed(mCommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Swap the back and front buffers
	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	// Advance the fence value to mark commands up to this fence point.
	mCurrFrameResource->Fence = ++mCurrentFence;

	// Add an instruction to the command queue to set a new fence point. 
	// Because we are on the GPU timeline, the new fence point won't be 
	// set until the GPU finishes processing all the commands prior to this Signal().
	mCommandQueue->Signal(mFence.Get(), mCurrentFence);

	/*		ANCIEN CODE
	ComponentRenderMesh oRMesh;
	DrawEdit(gt, oRMesh);
	*/
	
}

void InitDirect3DApp::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<D3DApp::RenderItem*>& ritems)
{
	UINT objCBByteSize = Utile::CalcConstantBufferByteSize(sizeof(D3DApp::ObjectConstants));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();

	// For each render item...
	for (size_t i = 0; i < ritems.size(); ++i)
	{
		auto ri = ritems[i];

		const D3D12_VERTEX_BUFFER_VIEW riVBV = ri->Geo->VertexBufferView();
		const D3D12_INDEX_BUFFER_VIEW riIBV = ri->Geo->IndexBufferView();
		cmdList->IASetVertexBuffers(0, 1, &riVBV);
		cmdList->IASetIndexBuffer(&riIBV);
		cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

		// Offset to the CBV in the descriptor heap for this object and for this frame resource.
		UINT cbvIndex = mCurrFrameResourceIndex * (UINT)mOpaqueRitems.size() + ri->ObjCBIndex;
		auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
		cbvHandle.Offset(cbvIndex, mCbvSrvUavDescriptorSize);

		cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);

		cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
	}
}

void InitDirect3DApp::DrawEdit(const GameTimer& gt, ComponentRenderMesh& oRMesh)
{
	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(mDirectCmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	// Indicate a state transition on the resource usage.
	CD3DX12_RESOURCE_BARRIER titi = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
	mCommandList->ResourceBarrier(1, &titi);

	// Set the viewport and scissor rect.  This needs to be reset whenever the command list is reset.
	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	// Clear the back buffer and depth buffer.
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), Colors::LightSteelBlue, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	D3D12_CPU_DESCRIPTOR_HANDLE tata = CurrentBackBufferView();
	D3D12_CPU_DESCRIPTOR_HANDLE toto = DepthStencilView();
	mCommandList->OMSetRenderTargets(1, &tata, true, &toto);

	oRMesh.DrawRenderItem(mCommandList, mOpaqueRitems, mCbvHeap, mCbvSrvUavDescriptorSize);

	// Indicate a state transition on the resource usage.
	CD3DX12_RESOURCE_BARRIER tete = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	mCommandList->ResourceBarrier(1, &tete);

	// Done recording commands.
	ThrowIfFailed(mCommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// swap the back and front buffers
	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	// Wait until frame commands are complete.  
	// This waiting is inefficient and is done for simplicity.  
	FlushCommandQueue();
}


void InitDirect3DApp::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void InitDirect3DApp::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void InitDirect3DApp::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f * static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f * static_cast<float>(y - mLastMousePos.y));

		// Update angles based on input to orbit camera around box.
		mTheta += dx;
		mPhi += dy;

		// Restrict the angle mPhi.
		mPhi = MathHelper::Clamp(mPhi, 0.1f, XM_PI - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		// Make each pixel correspond to 0.2 unit in the scene.
		float dx = 0.05f * static_cast<float>(x - mLastMousePos.x);
		float dy = 0.05f * static_cast<float>(y - mLastMousePos.y);

		// Update the camera radius based on input.
		mRadius += dx - dy;

		// Restrict the radius.
		mRadius = MathHelper::Clamp(mRadius, 5.0f, 150.0f);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}