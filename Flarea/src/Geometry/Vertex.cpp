#include "flrpch.h"
#include "Vertex.h"

namespace FLR
{
	Vertex::Vertex(const Vertex& vertex)
	{  }

	Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texCoord)
		: pos(pos), normal(normal), texCoord(texCoord)
	{  }

	bool Vertex::operator==(const Vertex& vertex)
	{
		return this->pos == vertex.pos && this->texCoord == vertex.texCoord && this->normal == vertex.normal;
	}
}
