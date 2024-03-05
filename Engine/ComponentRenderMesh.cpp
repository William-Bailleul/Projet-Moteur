#include "ComponentRenderMesh.h"

ComponentRenderMesh::ComponentRenderMesh(GameObject* gameObjectPointer, GeometryHandler::Mesh meshRef, Shader* shaderRef, Texture* textureRef) :Component::Component(gameObjectPointer) {
	Init(meshRef, shaderRef, textureRef);
}

void ComponentRenderMesh::Init(GeometryHandler::Mesh meshRef, Shader* shaderRef, Texture* textureRef) {
	refMesh = meshRef;
	refShader = shaderRef;
	refTexture = textureRef;
}

ComponentRenderMesh::~ComponentRenderMesh() {
}
void ComponentRenderMesh::Init(GeometryHandler::Mesh meshRef, Shader* shaderRef, Texture* textureRef)
{

	GeometryHandler::Mesh mesh = meshRef;

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	UINT meshVertexOffset = 0;

	// Cache the starting index for each object in the concatenated index buffer.
	UINT meshIndexOffset = 0;

	// Define the SubmeshGeometry that cover different 
	// regions of the vertex/index buffers.

	SubmeshGeometry boxSubmesh;
	boxSubmesh.IndexCount = (UINT)mesh.Indices32.size();
	boxSubmesh.StartIndexLocation = boxIndexOffset;
	boxSubmesh.BaseVertexLocation = boxVertexOffset;

	auto meshRitem = std::make_unique<RenderItem>();
	XMStoreFloat4x4(&meshRitem->World, DirectX::XMMatrixScaling(2.0f, 2.0f, 2.0f) * DirectX::XMMatrixTranslation(0.0f, 0.5f, 0.0f));
	meshRitem->ObjCBIndex = 0;
	meshRitem->Geo = mGeometries["shapeGeo"].get();
	meshRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	meshRitem->IndexCount = meshRitem->Geo->DrawArgs["mesh"].IndexCount;
	meshRitem->StartIndexLocation = meshRitem->Geo->DrawArgs["mesh"].StartIndexLocation;
	meshRitem->BaseVertexLocation = meshRitem->Geo->DrawArgs["mesh"].BaseVertexLocation;
	mAllRitems.push_back(std::move(meshRitem));
}