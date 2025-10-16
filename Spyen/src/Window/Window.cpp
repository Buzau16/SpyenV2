#include "Window.h"
#include <stdexcept>
#include <Core/Log.h>
#include <Core/Defines.h>


namespace Spyen {
	Window::Window(const WindowSpecifications& specs): m_Specs(specs)
	{
		SPY_CORE_INFO("Creating Window: {}x{} '{}'", specs.Width, specs.Height, specs.Title);
		SPY_CORE_ASSERT(glfwInit(), "Failed to initialize glfw!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_Window = glfwCreateWindow(m_Specs.Width, m_Specs.Height, m_Specs.Title.c_str(), nullptr, nullptr);
		SPY_CORE_ASSERT(m_Window, "Failed to create window");

		glfwMakeContextCurrent(m_Window);

		SPY_CORE_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to load OpenGL functions");
		SPY_CORE_INFO("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));
		SPY_CORE_INFO("GPU: {}", (const char*)glGetString(GL_RENDERER));

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glViewport(0, 0, m_Specs.Width, m_Specs.Height);

		glfwSetWindowUserPointer(m_Window, &m_Specs);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void Window::Clear(const float r, const float g, const float b, const float a) noexcept
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
