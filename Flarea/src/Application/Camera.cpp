#include "flrpch.h"
#include "Camera.h"

#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace FLR
{
	void Camera::ProcessEvent(const Event* const e)
	{
		//FLR_CORE_INFO("From Camera: {0}", e->ToString());
		if (e->GetEventType() == EventType::KeyPressed)
		{
			const KeyPressedEvent* const keyEvent = static_cast<const KeyPressedEvent* const>(e);
			if (keyEvent->GetKeyCode() == GLFW_KEY_W)
				camera_pos += camera_speed * camera_front;
			if (keyEvent->GetKeyCode() == GLFW_KEY_S)
				camera_pos -= camera_speed * camera_front;
			if (keyEvent->GetKeyCode() == GLFW_KEY_A)
				camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
			if (keyEvent->GetKeyCode() == GLFW_KEY_D)
				camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
		}
        if (e->GetEventType() == EventType::MouseMoved)
        {
            const MouseMovedEvent* const mouseEvent = static_cast<const MouseMovedEvent* const>(e);
            float xpos = static_cast<float>(mouseEvent->GetX());
            float ypos = static_cast<float>(mouseEvent->GetY());

            if (mouse_first)
            {
                lastX = xpos;
                lastY = ypos;
                mouse_first = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
            lastX = xpos;
            lastY = ypos;

            float sensitivity = 0.1f; // change this value to your liking
            xoffset *= sensitivity;
            yoffset *= sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;

            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            camera_front = glm::normalize(front);
        }
	}
}
