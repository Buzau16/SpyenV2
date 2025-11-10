#pragma once


#define NOMINMAX
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

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

		inline bool IsOpen() const noexcept { return !glfwWindowShouldClose(m_Window); };
		inline void SwapBuffers() const noexcept { glfwSwapBuffers(m_Window); };
		inline void PollEvents() noexcept { glfwPollEvents(); };
		void Clear(const float r, const float g, const float b, const float a = 1.0f) noexcept;

		[[nodiscard]] uint32_t GetWidth() const noexcept { return m_Specs.Width; }
		[[nodiscard]] uint32_t GetHeight() const noexcept { return m_Specs.Height; }

	private:
		WindowSpecifications m_Specs;
		GLFWwindow* m_Window;
	};
}

