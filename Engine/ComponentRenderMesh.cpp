#include "ComponentRenderMesh.h"

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

	// Define the SubmeshGeometry that cover different 
	// regions of the vertex/index buffers.

	meshSubmesh.IndexCount = (UINT)refMesh.Indices32.size();
	meshSubmesh.StartIndexLocation = meshIndexOffset;
	meshSubmesh.BaseVertexLocation = meshVertexOffset;

	totalVertexCount += refMesh.Vertices.size();

	std::vector<GeometryHandler::VertexPC> vertices(totalVertexCount);

	UINT k = 0;
	for (size_t i = 0; i < refMesh.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos = refMesh.Vertices[i].Position;
		vertices[k].Color = DirectX::XMFLOAT4(DirectX::Colors::DarkGreen);
	}

	std::vector<std::uint16_t> indices;
	indices.insert(indices.end(), std::begin(refMesh.GetIndices16()), std::end(refMesh.GetIndices16()));


	//BuildRenderItems();
}






ComponentRenderMesh::~ComponentRenderMesh() 
{

}
