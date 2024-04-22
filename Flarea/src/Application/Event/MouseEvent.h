#pragma once

#include "Event.h"

namespace FLR {
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) :
			m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Movement X: " << m_MouseX << " Y: " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float x, float y) :
			m_ScrollX(x), m_ScrollY(y) {}

		inline float GetX() const { return m_ScrollX; }
		inline float GetY() const { return m_ScrollY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scrolled X: " << m_ScrollX << " Y: " << m_ScrollY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	private:
		float m_ScrollX, m_ScrollY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_ButtonCode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	protected:
		MouseButtonEvent(int T) :
			m_ButtonCode(T) {}

		int m_ButtonCode;
	};

	class MouseButtonPressedEvent: public MouseButtonEvent
	{
	public:

		MouseButtonPressedEvent(int T) :
			MouseButtonEvent(T) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button " << m_ButtonCode << " Pressed";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int T) :
			MouseButtonEvent(T) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Button " << m_ButtonCode << " Released";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}