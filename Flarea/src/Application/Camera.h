#pragma once

namespace FLR
{
	class KeyEvent;

	class Camera
	{
	public:
		glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		const float camera_speed = 2.5f;

		void ProcessKeyEvent(const KeyEvent* const);
	};
}
