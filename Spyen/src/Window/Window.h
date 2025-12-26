#pragma once


#define NOMINMAX
#include <string>
#include <Events/Event.h>

struct GLFWwindow;

namespace Spyen {
	struct WindowSpecifications{
		uint32_t Width;
		uint32_t Height;
		std::string Title;
		
		using EventFnCallback = std::function<void(Event&)>;
		EventFnCallback callback;
	};

	class Window
	{
	public:
		Window() = default;
		Window(const WindowSpecifications& specs);
		~Window();

		bool IsOpen() const noexcept;
		void SwapBuffers() const noexcept;
		void PollEvents() noexcept;
		void Clear(const float r, const float g, const float b, const float a = 1.0f) noexcept;
		void RaiseEvent(Event& event);


		[[nodiscard]] uint32_t GetWidth() const noexcept { return m_Specs.Width; }
		[[nodiscard]] uint32_t GetHeight() const noexcept { return m_Specs.Height; }
		[[nodiscard]] GLFWwindow* GetWindowHandle() const noexcept { return m_Window; };

	private:
		WindowSpecifications m_Specs;
		GLFWwindow* m_Window;
	};
}

