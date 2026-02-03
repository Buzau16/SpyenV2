#pragma once
#include <functional>
#include <string>
#include <Core/Defines.h>

#define SP_SYNTHESIZE_EVENT_FUNC(type)				\
	static EventType GetStaticEventType() {		\
		return EventType::type;						\
	}											\
	EventType GetEventType() override { return GetStaticEventType();} \
	const char* GetName() override {return SP_STRINGIFY(type);}

enum class EventType {
	None = 0,
	KeyPressed, KeyReleased,
	WindowResized,
	MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
	EntityCreated, EntityDestroyed, EntityHit
};

namespace Spyen {
	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;
		virtual EventType GetEventType() = 0;
		virtual const char* GetName() = 0;

		// for debugging
		virtual std::string ToString() { return GetName(); }
		
		template <typename T>
		bool Is() { return GetEventType() == T::GetStaticEventType(); };

	public:
		bool Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}


		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticEventType() && !m_Event.Handled) {
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};
}

