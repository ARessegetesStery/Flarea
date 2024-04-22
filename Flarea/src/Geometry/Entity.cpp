#include "flrpch.h"
#include "Entity.h"

namespace FLR
{
	Entity::Entity()
	{
		this->entity_id = Entity::entity_count;
		++entity_count;
		this->mesh = Mesh();
	}

	Entity::Entity(const Mesh& mesh)
	{
		this->mesh = mesh;
	}

	Entity::Entity(const Entity& ent)
	{
		this->mesh = ent.GetMesh();
	}

	Entity& Entity::operator=(const Entity& ent)
	{
		this->mesh = ent.GetMesh();
		return *this;
	}

	void Entity::ClearMesh()
	{
		this->mesh.Clear();
	}

	void Entity::AddFaceToMesh(const Vertex& a, const Vertex& b, const Vertex& c)
	{
		this->mesh.AddFace(a, b, c);
	}

#ifdef FLR_DEBUG
	void Entity::Log() const
	{
		FLR_CORE_INFO("---- Logging Entity {0} ----", this->entity_id);
		FLR_CORE_TRACE("Mesh Info:");
		this->mesh.Log();
		FLR_CORE_INFO("---- End Logging Entity ----", this->entity_id);
	}
#endif
}
