#include "ComponentRenderMesh.h"
#include "ComponentCamera.h"
#include "Engine.h"
#include "Utile.h"


ComponentRenderMesh::ComponentRenderMesh(): Component(gameObjectPointer)
{
	
}

ComponentRenderMesh::ComponentRenderMesh(EngineObject* gameObjectPointer, 
	GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef): Component(gameObjectPointer)
{
	Init(meshRef, shaderRef, textureRef);

}

void ComponentRenderMesh::Init(EngineObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef)
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


	BuildRenderItems();
}

void ComponentRenderMesh::BuildRenderItems()
{
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

ComponentRenderMesh::~ComponentRenderMesh() 
{

}
