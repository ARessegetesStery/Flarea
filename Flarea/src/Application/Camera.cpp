#include "flrpch.h"
#include "Camera.h"

#include "Event/KeyEvent.h"

namespace FLR
{
	void Camera::ProcessKeyEvent(const KeyEvent* const e)
	{
		//FLR_CORE_INFO("From Camera: {0}", e->ToString());
		if (e->GetEventType() == EventType::KeyPressed)
		{
			const KeyPressedEvent* const keyEvent = static_cast<const KeyPressedEvent* const>(e);
			if (e->GetKeyCode() == GLFW_KEY_W)
				camera_pos += camera_speed * camera_front;
			if (e->GetKeyCode() == GLFW_KEY_S)
				camera_pos -= camera_speed * camera_front;
			if (e->GetKeyCode() == GLFW_KEY_A)
				camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
			if (e->GetKeyCode() == GLFW_KEY_D)
				camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
		}
	}
}
