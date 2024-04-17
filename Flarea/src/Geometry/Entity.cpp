#include "flrpch.h"
#include "Entity.h"

namespace FLR
{
	Entity::Entity()
	{
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
}
