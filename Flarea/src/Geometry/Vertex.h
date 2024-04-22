#pragma once

#include "glm/glm.hpp"

namespace FLR
{
	class Vertex
	{
	public:
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texture_coord;

		Vertex(const Vertex& vertex);
		Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 texture_coord);
		bool operator== (const Vertex& vertex) const;
	};
}
