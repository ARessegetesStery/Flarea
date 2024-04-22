#include "flrpch.h"
#include "Mesh.h"

namespace FLR
{
	void Mesh::AddFace(const Vertex& a, const Vertex& b, const Vertex& c)
	{
		std::array<size_t, 3> indices;
		std::array<const Vertex*, 3> vertices = { &a, &b, &c };
		for (size_t index = 0; index != 3; ++index)
		{
			auto iter = std::find(this->vertices.begin(), this->vertices.end(), *vertices[index]);
			if (iter == this->vertices.end())
			{
				this->vertices.emplace_back(*vertices[index]);
				indices[index] = this->vertices.size() - 1;
			}
			else
				indices[index] = iter - this->vertices.begin();
		}
		this->face_indices.push_back(indices);
	}

	void Mesh::Clear()
	{
		this->vertices.clear();
		this->face_indices.clear();
	}

	Mesh::Mesh()
	{
		this->vertices = {};
		this->face_indices = {};
	}

	Mesh::Mesh(const Mesh& m)
	{
		this->Clear();
		for (auto iter = m.vertices.begin(); iter != m.vertices.cend(); ++iter)
			this->vertices.push_back(*iter);
		for (auto iter = m.face_indices.begin(); iter != m.face_indices.cend(); ++iter)
			this->face_indices.push_back(*iter);
	}

	void Mesh::operator=(const Mesh& m)
	{
		this->Clear();
		for (auto iter = m.vertices.begin(); iter != m.vertices.cend(); ++iter)
			this->vertices.push_back(*iter);
		for (auto iter = m.face_indices.begin(); iter != m.face_indices.cend(); ++iter)
			this->face_indices.push_back(*iter);
	}

#ifdef FLR_DEBUG
	void Mesh::Log() const
	{
		FLR_CORE_INFO("----- Logging Mesh Info -----");
		FLR_CORE_TRACE("Vertices:");
		for (auto iter = this->vertices.begin(); iter != this->vertices.cend(); ++iter)
		{
			FLR_CORE_TRACE("Vertex {0}:", iter - this->vertices.cbegin());
			FLR_CORE_TRACE("| Position: {0}, {1}, {2}", iter->pos.x, iter->pos.y, iter->pos.z);
			FLR_CORE_TRACE("| Normal: {0}, {1}, {2}", iter->normal.x, iter->normal.y, iter->normal.z);
			FLR_CORE_TRACE("| Texture: {0}, {1}", iter->texture_coord.x, iter->texture_coord.y);
		}
		FLR_CORE_TRACE("Faces:");
		for (auto iter = this->face_indices.begin(); iter != this->face_indices.cend(); ++iter)
		{
			FLR_CORE_TRACE("Face {0}:", iter - this->face_indices.cbegin());
			FLR_CORE_TRACE("| Vertex 1: {0}", (*iter)[0]);
			FLR_CORE_TRACE("| Vertex 2: {0}", (*iter)[1]);
			FLR_CORE_TRACE("| Vertex 3: {0}", (*iter)[2]);
		}
		FLR_CORE_INFO("------ End Logging Mesh ------");
	}
#endif
}
