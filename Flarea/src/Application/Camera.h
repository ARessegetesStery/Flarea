#pragma once

namespace FLR
{
	class KeyEvent;

	class Camera
	{
	public:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		const float cameraSpeed = 2.5f;

		void ProcessKeyEvent(const KeyEvent* const);
	};
}
