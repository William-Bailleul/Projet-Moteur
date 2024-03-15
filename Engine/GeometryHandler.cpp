#include "GeometryHandler.h"
#include "Utile.h"
#include <algorithm>

using namespace DirectX;

GeometryHandler::Mesh GeometryHandler::BuildBox(float width, float height, float depth, uint32 subs)
{
	Mesh mesh;

	Vertex vertex[24];

	float w = 0.5f * width;
	float h = 0.5f * height;
	float d = 0.5f * depth;

	//Creation des Vertices (Points)

	//Face avant.
	vertex[0] = Vertex(-w, -h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[1] = Vertex(-w, +h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[2] = Vertex(+w, +h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	vertex[3] = Vertex(+w, -h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//Face arriere.
	vertex[4] = Vertex(-w, -h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertex[5] = Vertex(+w, -h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[6] = Vertex(+w, +h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[7] = Vertex(-w, +h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Face haut.
	vertex[8] = Vertex(-w, +h, -d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[9] = Vertex(-w, +h, +d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[10] = Vertex(+w, +h, +d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	vertex[11] = Vertex(+w, +h, -d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//Face bas.
	vertex[12] = Vertex(-w, -h, -d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertex[13] = Vertex(+w, -h, -d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[14] = Vertex(+w, -h, +d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[15] = Vertex(-w, -h, +d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Face gauche.
	vertex[16] = Vertex(-w, -h, +d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertex[17] = Vertex(-w, +h, +d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertex[18] = Vertex(-w, +h, -d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertex[19] = Vertex(-w, -h, -d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Face droite.
	vertex[20] = Vertex(+w, -h, -d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertex[21] = Vertex(+w, +h, -d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	vertex[22] = Vertex(+w, +h, +d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	vertex[23] = Vertex(+w, -h, +d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	mesh.Vertices.assign(&vertex[0], &vertex[24]);

	//Creation des indices (Triangles)

	uint32 indices[36];

	//Face avant.
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	//Face arriere.
	indices[6] = 4; indices[7] = 5; indices[8] = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 7;

	//Face haut.
	indices[12] = 8; indices[13] = 9; indices[14] = 10;
	indices[15] = 8; indices[16] = 10; indices[17] = 11;

	//Face bas.
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 12; indices[22] = 14; indices[23] = 15;

	//Face gauche.
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 16; indices[28] = 18; indices[29] = 19;

	//Face droite.
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 20; indices[34] = 22; indices[35] = 23;

	mesh.Indices32.assign(&indices[0], &indices[36]);

	//limite le nombre de subdivisions. (Si sub > 4u alors sub = 4u)
	subs = std::min<uint32>(subs, 4u);

	for (uint32 i = 0; i < subs; ++i)
		Subdivide(mesh);

	return mesh;
}

GeometryHandler::Mesh GeometryHandler::BuildBox(float width, float height, float depth, uint32 subs, bool inv)
{
	Mesh mesh;

	Vertex vertex[24];

	float w = 0.5f * width;
	float h = 0.5f * height;
	float d = 0.5f * depth;

	//Creation des Vertices (Points)

	//Face avant.
	vertex[0] = Vertex(-w, -h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[1] = Vertex(-w, +h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[2] = Vertex(+w, +h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	vertex[3] = Vertex(+w, -h, -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//Face arriere.
	vertex[4] = Vertex(-w, -h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertex[5] = Vertex(+w, -h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[6] = Vertex(+w, +h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[7] = Vertex(-w, +h, +d, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Face haut.
	vertex[8] = Vertex(-w, +h, -d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[9] = Vertex(-w, +h, +d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[10] = Vertex(+w, +h, +d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	vertex[11] = Vertex(+w, +h, -d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

	//Face bas.
	vertex[12] = Vertex(-w, -h, -d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	vertex[13] = Vertex(+w, -h, -d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	vertex[14] = Vertex(+w, -h, +d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	vertex[15] = Vertex(-w, -h, +d, 0.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//Face gauche.
	vertex[16] = Vertex(-w, -h, +d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vertex[17] = Vertex(-w, +h, +d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vertex[18] = Vertex(-w, +h, -d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vertex[19] = Vertex(-w, -h, -d, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	//Face droite.
	vertex[20] = Vertex(+w, -h, -d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	vertex[21] = Vertex(+w, +h, -d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	vertex[22] = Vertex(+w, +h, +d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	vertex[23] = Vertex(+w, -h, +d, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	mesh.Vertices.assign(&vertex[0], &vertex[24]);

	//Creation des indices (Triangles)

	uint32 indices[36];

	//Face avant.
	indices[0] = 2; indices[1] = 1; indices[2] = 0;
	indices[3] = 3; indices[4] = 2; indices[5] = 0;

	//Face arriere.
	indices[6] = 6; indices[7] = 5; indices[8] = 4;
	indices[9] = 7; indices[10] = 6; indices[11] = 4;

	//Face haut.
	indices[12] = 10; indices[13] = 9; indices[14] = 8;
	indices[15] = 11; indices[16] = 10; indices[17] = 8;

	//Face bas.
	indices[18] = 14; indices[19] = 13; indices[20] = 12;
	indices[21] = 15; indices[22] = 14; indices[23] = 12;

	//Face gauche.
	indices[24] = 18; indices[25] = 17; indices[26] = 16;
	indices[27] = 19; indices[28] = 18; indices[29] = 16;

	//Face droite.
	indices[30] = 22; indices[31] = 21; indices[32] = 20;
	indices[33] = 23; indices[34] = 22; indices[35] = 20;

	mesh.Indices32.assign(&indices[0], &indices[36]);

	//limite le nombre de subdivisions. (Si sub > 4u alors sub = 4u)
	subs = std::min<uint32>(subs, 4u);

	for (uint32 i = 0; i < subs; ++i)
		Subdivide(mesh);

	return mesh;
}

GeometryHandler::Mesh GeometryHandler::BuildSphere(float radius, uint32 sliceCount, uint32 stackCount)
{
	Mesh mesh;

	Vertex topVertex(0.0f, +radius, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	Vertex bottomVertex(0.0f, -radius, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	mesh.Vertices.push_back(topVertex);

	float phiStep = XM_PI / stackCount;
	float thetaStep = 2.0f * XM_PI / sliceCount;

	for (uint32 i = 1; i <= stackCount - 1; ++i)
	{
		float phi = i * phiStep;

		for (uint32 j = 0; j <= sliceCount; ++j)
		{
			float theta = j * thetaStep;

			Vertex vertex;

			vertex.Position.x = radius * sinf(phi) * cosf(theta);
			vertex.Position.y = radius * cosf(phi);
			vertex.Position.z = radius * sinf(phi) * sinf(theta);

			vertex.TanU.x = -radius * sinf(phi) * sinf(theta);
			vertex.TanU.y = 0.0f;
			vertex.TanU.z = +radius * sinf(phi) * cosf(theta);

			XMVECTOR T = XMLoadFloat3(&vertex.TanU);
			XMStoreFloat3(&vertex.TanU, XMVector3Normalize(T));

			XMVECTOR p = XMLoadFloat3(&vertex.Position);
			XMStoreFloat3(&vertex.Normal, XMVector3Normalize(p));

			vertex.TexC.x = theta / XM_2PI;
			vertex.TexC.y = phi / XM_PI;

			mesh.Vertices.push_back(vertex);
		}
	}

	mesh.Vertices.push_back(bottomVertex);

	for (uint32 i = 1; i <= sliceCount; ++i)
	{
		mesh.Indices32.push_back(0);
		mesh.Indices32.push_back(i + 1);
		mesh.Indices32.push_back(i);
	}

	uint32 baseIndex = 1;
	uint32 ringVertexCount = sliceCount + 1;
	for (uint32 i = 0; i < stackCount - 2; ++i)
	{
		for (uint32 j = 0; j < sliceCount; ++j)
		{
			mesh.Indices32.push_back(baseIndex + i * ringVertexCount + j);
			mesh.Indices32.push_back(baseIndex + i * ringVertexCount + j + 1);
			mesh.Indices32.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			mesh.Indices32.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			mesh.Indices32.push_back(baseIndex + i * ringVertexCount + j + 1);
			mesh.Indices32.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	uint32 southPoleIndex = (uint32)mesh.Vertices.size() - 1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (uint32 i = 0; i < sliceCount; ++i)
	{
		mesh.Indices32.push_back(southPoleIndex);
		mesh.Indices32.push_back(baseIndex + i);
		mesh.Indices32.push_back(baseIndex + i + 1);
	}

	return mesh;

}

GeometryHandler::Mesh GeometryHandler::BuildGeosphere(float radius, uint32 subs)
{
	Mesh mesh;

	//limite le nombre de subdivisions. (Si subs > 6u alors subs = 6u)
	subs = std::min<uint32>(subs, 6u);

	//Fait une aproximitee de sphere en utilisant un icosahedron.

	const float X = 0.525731f;
	const float Z = 0.850651f;

	XMFLOAT3 pos[12] =
	{
		XMFLOAT3(-X, 0.0f, Z),  XMFLOAT3(X, 0.0f, Z),
		XMFLOAT3(-X, 0.0f, -Z), XMFLOAT3(X, 0.0f, -Z),
		XMFLOAT3(0.0f, Z, X),   XMFLOAT3(0.0f, Z, -X),
		XMFLOAT3(0.0f, -Z, X),  XMFLOAT3(0.0f, -Z, -X),
		XMFLOAT3(Z, X, 0.0f),   XMFLOAT3(-Z, X, 0.0f),
		XMFLOAT3(Z, -X, 0.0f),  XMFLOAT3(-Z, -X, 0.0f)
	};

	uint32 k[60] =
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7
	};

	mesh.Vertices.resize(12);
	mesh.Indices32.assign(&k[0], &k[60]);

	for (uint32 i = 0; i < 12; ++i)
		mesh.Vertices[i].Position = pos[i];

	for (uint32 i = 0; i < subs; ++i)
		Subdivide(mesh);

	for (uint32 i = 0; i < mesh.Vertices.size(); ++i)
	{
		XMVECTOR n = XMVector3Normalize(XMLoadFloat3(&mesh.Vertices[i].Position));

		XMVECTOR p = radius * n;

		XMStoreFloat3(&mesh.Vertices[i].Position, p);
		XMStoreFloat3(&mesh.Vertices[i].Normal, n);

		float theta = atan2f(mesh.Vertices[i].Position.z, mesh.Vertices[i].Position.x);

		if (theta < 0.0f)
			theta += XM_2PI;

		float phi = acosf(mesh.Vertices[i].Position.y / radius);

		mesh.Vertices[i].TexC.x = theta / XM_2PI;
		mesh.Vertices[i].TexC.y = phi / XM_PI;

		mesh.Vertices[i].TanU.x = -radius * sinf(phi) * sinf(theta);
		mesh.Vertices[i].TanU.y = 0.0f;
		mesh.Vertices[i].TanU.z = +radius * sinf(phi) * cosf(theta);

		XMVECTOR T = XMLoadFloat3(&mesh.Vertices[i].TanU);
		XMStoreFloat3(&mesh.Vertices[i].TanU, XMVector3Normalize(T));
	}

	return mesh;
}

GeometryHandler::Mesh GeometryHandler::BuildCylinder(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount) 
{
	Mesh mesh;

	//Construit les couches.

	float stackHeight = height / stackCount;

	//Valeur a incrementer a chaque "pas".
	float radiusStep = (topRadius - bottomRadius) / stackCount;

	uint32 ringCount = stackCount + 1;

	//Creee les vertices de chaque anneau de couche de haut en bas.
	for (uint32 i = 0; i < ringCount; ++i)
	{
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;

		//Vertices d'anneau
		float dTheta = 2.0f * XM_PI / sliceCount;
		for (uint32 j = 0; j <= sliceCount; ++j)
		{
			Vertex vertex;

			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);

			vertex.Position = XMFLOAT3(r * c, y, r * s);

			vertex.TexC.x = (float)j / sliceCount;
			vertex.TexC.y = 1.0f - (float)i / stackCount;
			vertex.TanU = XMFLOAT3(-s, 0.0f, c);

			float dr = bottomRadius - topRadius;
			XMFLOAT3 bitangent(dr * c, -height, dr * s);

			XMVECTOR T = XMLoadFloat3(&vertex.TanU);
			XMVECTOR B = XMLoadFloat3(&bitangent);
			XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));
			XMStoreFloat3(&vertex.Normal, N);

			mesh.Vertices.push_back(vertex);
		}
	}

	uint32 ringVertexCount = sliceCount + 1;

	//Creee les indices pour chaque couches.
	for (uint32 i = 0; i < stackCount; ++i)
	{
		for (uint32 j = 0; j < sliceCount; ++j)
		{
			mesh.Indices32.push_back(i * ringVertexCount + j);
			mesh.Indices32.push_back((i + 1) * ringVertexCount + j);
			mesh.Indices32.push_back((i + 1) * ringVertexCount + j + 1);

			mesh.Indices32.push_back(i * ringVertexCount + j);
			mesh.Indices32.push_back((i + 1) * ringVertexCount + j + 1);
			mesh.Indices32.push_back(i * ringVertexCount + j + 1);
		}
	}

	BuildCylinderTopCap(bottomRadius, topRadius, height, sliceCount, stackCount, mesh);
	BuildCylinderBottomCap(bottomRadius, topRadius, height, sliceCount, stackCount, mesh);

	return mesh;
}

void GeometryHandler::Subdivide(Mesh& mesh)
{
	//Sauvegarde une copy du mesh.
	Mesh inputCopy = mesh;


	mesh.Vertices.resize(0);
	mesh.Indices32.resize(0);

	//       v1
	//       *
	//      / \
	//     /   \
	//  m0*-----*m1
	//   / \   / \
	//  /   \ /   \
	// *-----*-----*
	// v0    m2     v2

	uint32 numTris = (uint32)inputCopy.Indices32.size() / 3;
	for (uint32 i = 0; i < numTris; ++i)
	{
		Vertex vertex0 = inputCopy.Vertices[inputCopy.Indices32[i * 3 + 0]];
		Vertex vertex1 = inputCopy.Vertices[inputCopy.Indices32[i * 3 + 1]];
		Vertex vertex2 = inputCopy.Vertices[inputCopy.Indices32[i * 3 + 2]];

		//Genere les centres.

		Vertex m0 = MidPoint(vertex0, vertex1);
		Vertex m1 = MidPoint(vertex1, vertex2);
		Vertex m2 = MidPoint(vertex0, vertex2);

		//Ajoute les nouveaux triangles.

		mesh.Vertices.push_back(vertex0); // 0
		mesh.Vertices.push_back(vertex1); // 1
		mesh.Vertices.push_back(vertex2); // 2
		mesh.Vertices.push_back(m0); // 3
		mesh.Vertices.push_back(m1); // 4
		mesh.Vertices.push_back(m2); // 5

		mesh.Indices32.push_back(i * 6 + 0);
		mesh.Indices32.push_back(i * 6 + 3);
		mesh.Indices32.push_back(i * 6 + 5);

		mesh.Indices32.push_back(i * 6 + 3);
		mesh.Indices32.push_back(i * 6 + 4);
		mesh.Indices32.push_back(i * 6 + 5);

		mesh.Indices32.push_back(i * 6 + 5);
		mesh.Indices32.push_back(i * 6 + 4);
		mesh.Indices32.push_back(i * 6 + 2);

		mesh.Indices32.push_back(i * 6 + 3);
		mesh.Indices32.push_back(i * 6 + 1);
		mesh.Indices32.push_back(i * 6 + 4);
	}
}

GeometryHandler::Vertex GeometryHandler::MidPoint(const Vertex& vertex0, const Vertex& vertex1)
{
	XMVECTOR p0 = XMLoadFloat3(&vertex0.Position);
	XMVECTOR p1 = XMLoadFloat3(&vertex1.Position);

	XMVECTOR n0 = XMLoadFloat3(&vertex0.Normal);
	XMVECTOR n1 = XMLoadFloat3(&vertex1.Normal);

	XMVECTOR tan0 = XMLoadFloat3(&vertex0.TanU);
	XMVECTOR tan1 = XMLoadFloat3(&vertex1.TanU);

	XMVECTOR tex0 = XMLoadFloat2(&vertex0.TexC);
	XMVECTOR tex1 = XMLoadFloat2(&vertex1.TexC);

	//Trouve les centres des vecteurs et les normalise 
	XMVECTOR pos = 0.5f * (p0 + p1);
	XMVECTOR normal = XMVector3Normalize(0.5f * (n0 + n1));
	XMVECTOR tangent = XMVector3Normalize(0.5f * (tan0 + tan1));
	XMVECTOR tex = 0.5f * (tex0 + tex1);

	Vertex vertex;
	XMStoreFloat3(&vertex.Position, pos);
	XMStoreFloat3(&vertex.Normal, normal);
	XMStoreFloat3(&vertex.TanU, tangent);
	XMStoreFloat2(&vertex.TexC, tex);

	return vertex;
}

void GeometryHandler::BuildCylinderTopCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, Mesh& mesh)
{
	uint32 baseIndex = (uint32)mesh.Vertices.size();

	float y = 0.5f * height;
	float dTheta = 2.0f * XM_PI / sliceCount;

	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		float x = topRadius * cosf(i * dTheta);
		float z = topRadius * sinf(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		mesh.Vertices.push_back(Vertex(x, y, z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	mesh.Vertices.push_back(Vertex(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	uint32 centerIndex = (uint32)mesh.Vertices.size() - 1;

	for (uint32 i = 0; i < sliceCount; ++i)
	{
		mesh.Indices32.push_back(centerIndex);
		mesh.Indices32.push_back(baseIndex + i + 1);
		mesh.Indices32.push_back(baseIndex + i);
	}
}

void GeometryHandler::BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, Mesh& mesh)
{
	uint32 baseIndex = (uint32)mesh.Vertices.size();

	float y = -0.5f * height;
	float dTheta = 2.0f * XM_PI / sliceCount;

	for (uint32 i = 0; i <= sliceCount; ++i)
	{
		float x = bottomRadius * cosf(i * dTheta);
		float z = bottomRadius * sinf(i * dTheta);

		float u = x / height + 0.5f;
		float v = z / height + 0.5f;

		mesh.Vertices.push_back(Vertex(x, y, z, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, u, v));
	}

	mesh.Vertices.push_back(Vertex(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f));

	uint32 centerIndex = (uint32)mesh.Vertices.size() - 1;

	for (uint32 i = 0; i < sliceCount; ++i)
	{
		mesh.Indices32.push_back(centerIndex);
		mesh.Indices32.push_back(baseIndex + i);
		mesh.Indices32.push_back(baseIndex + i + 1);
	}
}

GeometryHandler::Mesh GeometryHandler::BuildPyramid(float size, uint32 state)
{
	Mesh meshData;

	float w = size;
	float h = size;
	float d = size;

	Vertex vertex[8];
	uint32 indices[24];

	switch (state)
	{
	case 2:

		//set points
		vertex[0] = Vertex(-w, -h, -d, -1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vertex[1] = Vertex(0.0f, +h, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vertex[2] = Vertex(+w, -h, -d, +1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		vertex[3] = Vertex(0.0f, -h, +d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		vertex[4] = Vertex(0.0f, -(3 * h), 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);

		meshData.Vertices.assign(&vertex[0], &vertex[5]);

		//set verteces
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 1; indices[5] = 3;
		indices[6] = 3; indices[7] = 1; indices[8] = 0;
		indices[9] = 2; indices[10] = 4; indices[11] = 0;
		indices[12] = 0; indices[13] = 4; indices[14] = 3;
		indices[15] = 3; indices[16] = 4; indices[17] = 2;

		meshData.Indices32.assign(&indices[0], &indices[18]);

		break;

	case 3:

		w *= 3;
		h *= 3;
		d *= 3;

		//set points
		vertex[0] = Vertex(-w, -h, -d, -1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vertex[1] = Vertex(0.0f, +h, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vertex[2] = Vertex(+w, -h, -d, +1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		vertex[3] = Vertex(0.0f, -h, +d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		meshData.Vertices.assign(&vertex[0], &vertex[4]);

		//set verteces
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 1; indices[5] = 3;
		indices[6] = 3; indices[7] = 1; indices[8] = 0;
		indices[9] = 0; indices[10] = 2; indices[11] = 3;

		meshData.Indices32.assign(&indices[0], &indices[12]);

		Subdivide(meshData);

		break;

	case 4:

		w *= 3;
		h *= 3;
		d *= 3;

		//set points
		vertex[0] = Vertex(-w, -h, -d, -1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vertex[1] = Vertex(0.0f, +h, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vertex[2] = Vertex(+w, -h, -d, +1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		vertex[3] = Vertex(0.0f, -h, +d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
		vertex[4] = Vertex(+w, +h - (h * 0.75), +d, -1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vertex[5] = Vertex(0.0f, -h - (h * 0.75), 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vertex[6] = Vertex(-w, +h - (h * 0.75), +d, +1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		vertex[7] = Vertex(0.0f, +h - (h * 0.75), -d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		meshData.Vertices.assign(&vertex[0], &vertex[8]);

		//set verteces
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 1; indices[5] = 3;
		indices[6] = 3; indices[7] = 1; indices[8] = 0;
		indices[9] = 0; indices[10] = 2; indices[11] = 3;
		indices[12] = 6; indices[13] = 5; indices[14] = 4;
		indices[15] = 7; indices[16] = 5; indices[17] = 6;
		indices[18] = 4; indices[19] = 5; indices[20] = 7;
		indices[21] = 7; indices[22] = 6; indices[23] = 4;

		meshData.Indices32.assign(&indices[0], &indices[24]);


		break;

	default:

		//set points
		vertex[0] = Vertex(-w, -h, -d, -1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		vertex[1] = Vertex(0.0f, +h, 0.0f, 0.0f, +1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
		vertex[2] = Vertex(+w, -h, -d, +1.0f, 0.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		vertex[3] = Vertex(0.0f, -h, +d, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f);

		meshData.Vertices.assign(&vertex[0], &vertex[4]);

		//set verteces
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 2; indices[4] = 1; indices[5] = 3;
		indices[6] = 3; indices[7] = 1; indices[8] = 0;
		indices[9] = 2; indices[10] = 3; indices[11] = 0;

		meshData.Indices32.assign(&indices[0], &indices[12]);

		break;
	}

	return meshData;
}