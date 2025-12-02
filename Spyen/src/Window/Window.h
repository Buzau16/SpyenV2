#pragma once


#define NOMINMAX
#include <string>

struct GLFWwindow;

namespace Spyen {
	struct WindowSpecifications{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
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

		[[nodiscard]] uint32_t GetWidth() const noexcept { return m_Specs.Width; }
		[[nodiscard]] uint32_t GetHeight() const noexcept { return m_Specs.Height; }
		[[nodiscard]] GLFWwindow* GetWindowHandle() const noexcept { return m_Window; };

	private:
		WindowSpecifications m_Specs;
		GLFWwindow* m_Window;
	};
}

