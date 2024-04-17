#include "flrpch.h"
#include "Camera.h"

#include "Event/KeyEvent.h"

namespace FLR
{
	void Camera::ProcessKeyEvent(const KeyEvent* const e)
	{
		if (e->GetEventType() == EventType::KeyPressed)
		{
			const KeyPressedEvent* const keyEvent = static_cast<const KeyPressedEvent* const>(e);
			if (e->GetKeyCode() == GLFW_KEY_W)
				cameraPos += cameraSpeed * cameraFront;
			if (e->GetKeyCode() == GLFW_KEY_S)
				cameraPos -= cameraSpeed * cameraFront;
			if (e->GetKeyCode() == GLFW_KEY_A)
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			if (e->GetKeyCode() == GLFW_KEY_D)
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}
	}
}
