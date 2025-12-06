#pragma once
#include <Events/Event.h>
#include <Input/KeyCodes.h>

namespace Spyen{
	class KeyEvent : public Event {
	public:
		inline KeyCode GetKeyCode() const { return m_Keycode; };
	protected:
		KeyEvent(KeyCode code) : m_Keycode(code) {}
		KeyCode m_Keycode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(KeyCode code, bool is_reapeated)
			: KeyEvent(code), m_IsRepeated(is_reapeated) {
		}

		inline bool IsRepeated() const { return m_IsRepeated; };

		SP_SYNTHESIZE_EVENT_FUNC(KeyPressed);

	private:
		bool m_IsRepeated = false;
	};

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(KeyCode code) : KeyEvent(code) {}
		SP_SYNTHESIZE_EVENT_FUNC(KeyReleased)
	};
}