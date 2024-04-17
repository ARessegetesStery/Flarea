#include "flrpch.h"
#include "Mesh.h"

namespace FLR
{
	void Mesh::AddFace(const Vertex& a, const Vertex& b, const Vertex& c)
	{
		bool ARep = false, BRep = false, CRep = false;
		size_t AIndex = 0, BIndex = 0, CIndex = 0;
		size_t CurIndex = static_cast<size_t>(this->vertices.size());
		std::array<size_t, 3> indices;
		for (auto iter = vertices.begin(); iter != vertices.cend(); ++iter)
		{
			if (!ARep && *iter == a)
			{
				AIndex = static_cast<size_t>(iter - vertices.cbegin());
				ARep = true;
			}
			if (!BRep && *iter == b)
			{
				BIndex = static_cast<size_t>(iter - vertices.cbegin());
				BRep = true;
			}
			if (!CRep && *iter == c)
			{
				CIndex = static_cast<size_t>(iter - vertices.cbegin());
				CRep = true;
			}
			if (ARep && BRep && CRep)
				break;
		}

		if (ARep)
			indices[0] = AIndex;
		else
		{
			this->vertices.push_back(a);
			indices[0] = CurIndex;
			++CurIndex;
		}
		if (BRep)
			indices[1] = BIndex;
		else
		{
			this->vertices.push_back(b);
			indices[1] = CurIndex;
			++CurIndex;
		}
		if (CRep)
			indices[2] = CIndex;
		else
		{
			this->vertices.push_back(c);
			indices[2] = CurIndex;
			++CurIndex;
		}

		this->faceIndices.emplace_back(indices);
	}

	void Mesh::Clear()
	{
		this->vertices.clear();
		this->faceIndices.clear();
	}

	Mesh::Mesh()
	{
		this->vertices = {};
		this->faceIndices = {};
	}

	Mesh::Mesh(const Mesh& m)
	{
		this->Clear();
		for (auto iter = m.vertices.begin(); iter != m.vertices.cend(); ++iter)
			this->vertices.push_back(*iter);
		for (auto iter = m.faceIndices.begin(); iter != m.faceIndices.cend(); ++iter)
			this->faceIndices.push_back(*iter);
	}

	void Mesh::operator=(const Mesh& m)
	{
		this->Clear();
		for (auto iter = m.vertices.begin(); iter != m.vertices.cend(); ++iter)
			this->vertices.push_back(*iter);
		for (auto iter = m.faceIndices.begin(); iter != m.faceIndices.cend(); ++iter)
			this->faceIndices.push_back(*iter);
	}
}
