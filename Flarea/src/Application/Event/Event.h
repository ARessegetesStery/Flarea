#pragma once

// currently blocking:
// will not proceed until all events are properly handled

#include "flrpch.h"

namespace FLR {

	enum class EventType
	{
		// Window Focus = Window become active
		None = 0,
		WindowClosed, WindowResized, WindowFocus, WindowLostFocus, WindowMoved,
		AppUpdate, AppTick, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		EventCategoryApplication   = BIT(0),
		EventCategoryInput         = BIT(1),
		EventCategoryKeyboard      = BIT(2),
		EventCategoryMouse         = BIT(3),
	//	EventCategoryMousePressed  = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)  \
	static EventType GetStaticEventType() { return EventType::##type; }\
	virtual EventType GetEventType() const override { return GetStaticEventType(); }\
	virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual int GetEventCategory() const override { return category; }
	// not using ## token modifier because one mask may contain several bitfields

	class Event
	{
		friend class EventDispatcher;

	public:
		// virtual EventType GetStaticEventType() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;

		virtual int GetEventCategory() const = 0;

		virtual std::string ToString() const { return GetName(); }

		inline bool IsOfSameCategory(EventCategory E) const
		{
			return (GetEventCategory() & E);
		}

		inline bool isHandled() { return m_Handled; }

	protected:
		bool m_Handled = false;

	};

	// HACK unsure whether needs SPARKS_API modifier
	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;
		// For every type of Event there should exist a corresponding function
		// which specify whether the event has been handled or the event
		// should be further dispatched

	public:
		EventDispatcher(Event& e) : m_Event(e) {}

		template <typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticEventType())
			{
				m_Event.m_Handled = func(*((T*)&m_Event));
				return true;
			}
				return false;
		}

	private:
		Event& m_Event;

	};

}