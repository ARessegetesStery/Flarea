#include "flrpch.h"
#include "Vertex.h"

namespace FLR
{
	Vertex::Vertex(const Vertex& vertex)
		: pos(vertex.pos), normal(vertex.normal), texture_coord(vertex.texture_coord)
	{  }

	Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texture_coord)
		: pos(pos), normal(normal), texture_coord(texture_coord)
	{  }

	bool Vertex::operator==(const Vertex& vertex) const
	{
		return (this->pos == vertex.pos) && (this->texture_coord == vertex.texture_coord) && (this->normal == vertex.normal);
	}
}
