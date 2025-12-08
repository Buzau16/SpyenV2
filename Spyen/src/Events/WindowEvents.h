#pragma once
#include <Events/Event.h>

namespace Spyen {
	class WindowResizedEvent : public Event {
	public:
		WindowResizedEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height){}

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		SP_SYNTHESIZE_EVENT_FUNC(WindowResized);

	private:
		uint32_t m_Width, m_Height;
	};
}