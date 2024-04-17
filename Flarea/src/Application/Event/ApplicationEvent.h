#pragma once

#include "Event.h"

namespace FLR {

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int XRes, unsigned int YRes)
			: m_XRes(XRes), m_YRes(YRes) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Resized. Width: " << m_XRes << " Height: " << m_YRes;
			return ss.str();
		}

		inline unsigned int GetWidth() { return m_XRes; }
		inline unsigned int GetHeight() { return m_YRes; }

		EVENT_CLASS_TYPE(WindowResized);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);

	private:
		unsigned int m_XRes, m_YRes;

	};

	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window Closed!";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClosed);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class AppTick : public Event
	{
	public:
		AppTick();

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class AppUpdate : public Event
	{
	public:
		AppUpdate();

		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class AppRender : public Event
	{
	public:
		AppRender();

		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}