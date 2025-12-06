#pragma once
#include <Events/Event.h>
#include <Math/Vector/Vec.h>
#include <Input/MouseCodes.h>


namespace Spyen {
	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_Pos({ x, y }) {}

		SP_SYNTHESIZE_EVENT_FUNC(MouseMoved)
	private:
		Vec2 m_Pos;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x, float y) : m_Offset({ x, y }) {}

		SP_SYNTHESIZE_EVENT_FUNC(MouseScrolled)
	private:
		Vec2 m_Offset;

	};

	class MouseButtonEvent : public Event {
	public:
		inline MouseCode GetMouseButton() const { return m_MouseButton; }
	protected:
		MouseButtonEvent(MouseCode code) : m_MouseButton(code) {}
		MouseCode m_MouseButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(MouseCode code) : MouseButtonEvent(code) {}

		SP_SYNTHESIZE_EVENT_FUNC(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(MouseCode code) : MouseButtonEvent(code) {}

		SP_SYNTHESIZE_EVENT_FUNC(MouseButtonReleased)
	};
}