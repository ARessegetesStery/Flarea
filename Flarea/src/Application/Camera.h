#pragma once

namespace FLR
{
	class Event;

	class Camera
	{
	public:
		glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
		float fov = 45.f;
		float yaw = -90.0f;
		float pitch = 0.0f;
		float lastX = 800.0f / 2.0;
		float lastY = 600.0 / 2.0;

		const float camera_speed = .25f;

		bool mouse_first = false;

		void ProcessEvent(const Event* const);
	};
}
