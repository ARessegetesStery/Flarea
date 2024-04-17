#pragma once

#include "Event.h"

namespace FLR {

	class KeyEvent : public Event
	{
	public:
		inline unsigned int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(unsigned int KeyCode) : m_KeyCode(KeyCode) {}
		unsigned int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(unsigned int KeyCode, unsigned int RepeatCnt):
			KeyEvent(KeyCode), m_RepeatCnt(RepeatCnt) {}
		// delegating constructor

		inline unsigned int GetRepeatCnt() { return m_RepeatCnt; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key \'"<< m_KeyCode << "\' Pressed, repeated " << m_RepeatCnt << " time(s).";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		unsigned int m_RepeatCnt;

	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(unsigned int KeyCode) :
			KeyEvent(KeyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Key \'" << m_KeyCode << "\' Released.";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}
