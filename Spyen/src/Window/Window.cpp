#include "Window.h"
#include <stdexcept>
#include <Core/Log.h>


namespace Spyen {
	Window::Window(const WindowSpecifications& specs): m_Specs(specs)
	{
		SPY_CORE_INFO("Creating Window: Dimensions: {}x{}, Title: '{}'", specs.Width, specs.Height, specs.Title);
		if (!glfwInit())
		{
			SPY_CORE_ERROR("Failed to initialize glfw!");
		}
		//SPY_CORE_ASSERT(glfwInit(), "Failed to initialize glfw!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		m_Window = glfwCreateWindow(m_Specs.Width, m_Specs.Height, m_Specs.Title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			SPY_CORE_ERROR("Failed to create window");
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(m_Window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			SPY_CORE_CRITICAL("Failed to load OpenGL functions");
		}

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
