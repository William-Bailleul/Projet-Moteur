#include "ComponentRenderMesh.h"

ComponentRenderMesh::ComponentRenderMesh(): Component(gameObjectPointer)
{
	
}

ComponentRenderMesh::ComponentRenderMesh(GameObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef): Component(gameObjectPointer)
{
	Init(meshRef, shaderRef, textureRef);
}

void ComponentRenderMesh::Init(GameObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef)
{
	Init(meshRef, shaderRef, textureRef);
}

void ComponentRenderMesh::Init(GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef) {
	refMesh = meshRef;
	refShader = shaderRef;
	refTexture = textureRef;

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	UINT meshVertexOffset = 0;

	// Cache the starting index for each object in the concatenated index buffer.
	UINT meshIndexOffset = 0;

	// Define the SubmeshGeometry that cover different 
	// regions of the vertex/index buffers.

	SubmeshGeometry meshSubmesh;
	meshSubmesh.IndexCount = (UINT)refMesh.Indices32.size();
	meshSubmesh.StartIndexLocation = meshIndexOffset;
	meshSubmesh.BaseVertexLocation = meshVertexOffset;

	auto totalVertexCount =
		refMesh.Vertices.size();

	std::vector<Vertex> vertices(totalVertexCount);

	UINT k = 0;
	for (size_t i = 0; i < refMesh.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = refMesh.Vertices[i].Position;
		vertices[k].Color = DirectX::XMFLOAT4(DirectX::Colors::DarkGreen);
	}

	std::vector<std::uint16_t> indices;
	indices.insert(indices.end(), std::begin(refMesh.GetIndices16()), std::end(refMesh.GetIndices16()));


}

void ComponentRenderMesh::BuildRenderItems()
{
	auto meshRitem = std::make_unique<D3DApp::RenderItem>();
	XMStoreFloat4x4(&meshRitem->World, DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f) * DirectX::XMMatrixTranslation(0.0f, 0.5f, 0.0f));
	meshRitem->ObjCBIndex = 0;
	meshRitem->Geo = mGeometries["shapeGeo"].get();
	meshRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	meshRitem->IndexCount = meshRitem->Geo->DrawArgs["mesh"].IndexCount;
	meshRitem->StartIndexLocation = meshRitem->Geo->DrawArgs["mesh"].StartIndexLocation;
	meshRitem->BaseVertexLocation = meshRitem->Geo->DrawArgs["mesh"].BaseVertexLocation;
	mAllRitems.push_back(std::move(meshRitem));

	// All the render items are opaque.
	for (auto& e : mAllRitems)
		mOpaqueRitems.push_back(e.get());
}

void ComponentRenderMesh::DrawRenderItem(Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList, const std::vector<D3DApp::RenderItem*>& ritems, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap, UINT mCbvSrvUavDescriptorSize)
{
	UINT objCBByteSize = Utile::CalcConstantBufferByteSize(sizeof(DirectX::XMFLOAT4X4));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();

	// For each render item...
	for (size_t i = 0; i < ritems.size(); ++i)
	{
		auto ri = ritems[i];

		D3D12_VERTEX_BUFFER_VIEW vBV = ri->Geo->VertexBufferView();
		cmdList->IASetVertexBuffers(0, 1, &vBV);
		D3D12_INDEX_BUFFER_VIEW iBV = ri->Geo->IndexBufferView();
		cmdList->IASetIndexBuffer(&iBV);
		cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

		// Offset to the CBV in the descriptor heap for this object and for this frame resource.
		UINT cbvIndex = mCurrFrameResourceIndex * (UINT)mOpaqueRitems.size() + ri->ObjCBIndex;
		auto cbvHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
		cbvHandle.Offset(cbvIndex, mCbvSrvUavDescriptorSize);

		cmdList->SetGraphicsRootDescriptorTable(0, cbvHandle);

		cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
	}
}

void ComponentRenderMesh::UpdateObjectCBs(const GameTimer& gt)
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

/*
void ComponentRenderMesh::UpdateMainPassCB(const GameTimer& gt)
{
	XMMATRIX view = XMLoadFloat4x4(&mView);
	XMMATRIX proj = XMLoadFloat4x4(&mProj);

	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);

	XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
	XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
	XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
	XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
	XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	mMainPassCB.EyePosW = mEyePos;
	mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
	mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
	mMainPassCB.NearZ = 1.0f;
	mMainPassCB.FarZ = 1000.0f;
	mMainPassCB.TotalTime = gt.TotalTime();
	mMainPassCB.DeltaTime = gt.DeltaTime();

	auto currPassCB = mCurrFrameResource->PassCB.get();
	currPassCB->CopyData(0, mMainPassCB);
}
*/

ComponentRenderMesh::~ComponentRenderMesh() 
{

}