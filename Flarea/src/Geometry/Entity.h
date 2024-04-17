#pragma once

#include "Mesh.h"

namespace FLR
{
	class Entity
	{
		friend class Renderer;
		friend class AssetManager;
	public:
		Entity();
		Entity(const Mesh&);
		Entity(const Entity&);

		Entity& operator= (const Entity&);

		inline const Mesh& GetMesh() const { return this->mesh; }
		// Directly acts on mesh; call corresponding functions of class {Mesh}

		void ClearMesh();
		void AddFaceToMesh(const Vertex&, const Vertex&, const Vertex&);

	private:
		// UID of Entity is generated (assigned) upon construction or copy; and cannot be changed by outside
		Mesh mesh;
	};
}
