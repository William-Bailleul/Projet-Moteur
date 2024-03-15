#pragma once

#include "Utile.h"

class GeometryHandler
{
public:

	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;

	struct Vertex
	{
		Vertex(){}
		Vertex(
			const DirectX::XMFLOAT3& p,
			const DirectX::XMFLOAT3& n,
			const DirectX::XMFLOAT3& t,
			const DirectX::XMFLOAT2& uv) :
			Position(p),
			Normal(n),
			TanU(t),
			TexC(uv) {}
		Vertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v) :
			Position(px, py, pz),
			Normal(nx, ny, nz),
			TanU(tx, ty, tz),
			TexC(u, v) {}

		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT3 TanU;
		DirectX::XMFLOAT2 TexC;
	};

	struct Mesh
	{
		Mesh(){}

		std::vector<Vertex> Vertices;
		std::vector<uint32> Indices32;

		std::vector<uint16>& GetIndices16()
		{
			if (mIndices16.empty())
			{
				mIndices16.resize(Indices32.size());
				for (size_t i = 0; i < Indices32.size(); ++i)
					mIndices16[i] = static_cast<uint16>(Indices32[i]);
			}

			return mIndices16;
		}

	private:
		std::vector<uint16> mIndices16;
	};

	//MESH-BUILDING FUNCTIONS HERE, MAKE THEM RETURN A Mesh OR A Mesh REFERENCE

	//BuildBox - Creee une boite en prennant une largeur width, une hauteur height, une profondeur depth 
	//et a sub coupures verticales et horizontales sur chaques faces
	Mesh BuildBox(float width, float height, float depth, uint32 subs);
	Mesh BuildBox(float width, float height, float depth, uint32 subs, bool inv);


	//BuildSphere - Creee une sphere en prennant une rayon radius, un nombre de tranches verticales sliceCount 
	//et horizontale stackCount (ces deux parametres controllent la tesselation)
	Mesh BuildSphere(float radius, uint32 sliceCount, uint32 stackCount);

	//BuildGeosphere - Creee une sphere a partir d'un icosahedron (polyhedron a 20 faces identiques), prends un rayon radius 
	//et un niveau de tesselation sub (plus sub est eleve plus la sphere sera arrondie)
	//(utile pour faire des formes plus completes)
	Mesh BuildGeosphere(float radius, uint32 subs);

	//BuildCylinder - Creee un cylindre en prennant un rayon de bases bottomRadius et topRadius, une hauteur height, 
	//un nombre de tranches sliceCount et couches stackCount (ces deux parametres controllent la tesselation)
	Mesh BuildCylinder(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount);

	//BuildCylinder - Creee un cylindre en prennant un rayon de bases bottomRadius et topRadius, une hauteur height, 
	//un nombre de tranches sliceCount et couches stackCount (ces deux parametres controllent la tesselation)
	GeometryHandler::Mesh BuildPyramid(float size, uint32 state);

private:
	//Decoupe une face en 4 parties egales en utilisant les centres des vertices
	void Subdivide(Mesh& mesh);

	//Determine les centres des vertices entre deux points
	Vertex MidPoint(const Vertex& v0, const Vertex& v1);

	//Construit les bases d'un Cylindre
	void BuildCylinderTopCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, Mesh& mesh);
	void BuildCylinderBottomCap(float bottomRadius, float topRadius, float height, uint32 sliceCount, uint32 stackCount, Mesh& mesh);
};

