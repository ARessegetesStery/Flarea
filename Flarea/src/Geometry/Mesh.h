#pragma once

#include "Vertex.h"

namespace FLR
{
	class Mesh
	{
	public:
		friend class Renderer;

		void AddFace(const Vertex&, const Vertex&, const Vertex&);

		inline bool Empty() const { return vertices.empty(); }
		void Clear();

		Mesh();
		Mesh(const Mesh& m);

		void operator= (const Mesh& m);

#ifdef FLR_DEBUG
		void Log() const;
#endif

	public:
		vector<Vertex> vertices;
		vector<std::array<size_t, 3>> face_indices;
	};
}
