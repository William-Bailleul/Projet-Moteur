#include "ComponentRenderMesh.h"

ComponentRenderMesh::ComponentRenderMesh(GameObject* gameObjectPointer, GeometryHandler::Mesh& meshRef, Shader* shaderRef, Texture* textureRef): Component(gameObjectPointer)
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

void ComponentRenderMesh::DrawRenderItem(ID3D12GraphicsCommandList* cmdList, const std::vector<D3DApp::RenderItem*>& ritems, Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mCbvHeap, UINT mCbvSrvUavDescriptorSize)
{
	UINT objCBByteSize = Utile::CalcConstantBufferByteSize(sizeof(DirectX::XMFLOAT4X4));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();

	// For each render item...
	for (size_t i = 0; i < ritems.size(); ++i)
	{
		auto ri = ritems[i];

		cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
		cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
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

ComponentRenderMesh::FrameResource::FrameResource(ID3D12Device* device, UINT passCount, UINT objectCount)
{
	ThrowIfFailed(device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(CmdListAlloc.GetAddressOf())));

	PassCB = std::make_unique<UploadBuffer<PassConstants>>(device, passCount, true);
	ObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(device, objectCount, true);
}

ComponentRenderMesh::FrameResource::~FrameResource()
{

}