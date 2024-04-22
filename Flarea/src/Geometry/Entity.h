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

		inline uint32_t GetEntityID() const { return this->entity_id; }
		inline const Mesh& GetMesh() const { return this->mesh; }
		inline glm::vec3 GetPosition() const { return this->position; }
		inline float GetRotation() const { return this->rotation; }
		// Directly acts on mesh; call corresponding functions of class {Mesh}

		inline void SetPosition(glm::vec3 pos) { this->position = pos; }
		inline void SetRotation(float rot) { this->rotation = rot; }

		void ClearMesh();
		void AddFaceToMesh(const Vertex&, const Vertex&, const Vertex&);

#ifdef FLR_DEBUG
		void Log() const;
#endif

	private:
		// UID of Entity is generated (assigned) upon construction or copy; and cannot be changed by outside
		glm::vec3 position;
		float rotation;
		uint32_t entity_id;
		Mesh mesh;

		static inline uint32_t entity_count = 0;
	};
}
