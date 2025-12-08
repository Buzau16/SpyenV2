#include "spypch.h"
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <Core/Log.h>
#include <Events/KeyEvents.h>
#include <Events/MouseEvents.h>
#include <Events/WindowEvents.h>


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

		glfwMakeContextCurrent(m_Window);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glViewport(0, 0, m_Specs.Width, m_Specs.Height);

		glfwSetWindowUserPointer(m_Window, &m_Specs);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* handle, int key, int scancode, int action, int mods) {
			Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle)));

			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, false);
				window.RaiseEvent(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				window.RaiseEvent(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, true);
				window.RaiseEvent(event);
				break;
			}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* handle, int button, int action, int mods) {
			Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle)));

			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				window.RaiseEvent(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				window.RaiseEvent(event);
				break;
			}
			}
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* handle, int width, int height) {
			Window& window = *(reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle)));
			window.m_Specs.Width = width;
			window.m_Specs.Height = height;
			glViewport(0, 0, width, height);
			WindowResizedEvent event(width, height);
			window.RaiseEvent(event);
		});
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	bool Window::IsOpen() const noexcept
	{
		return !glfwWindowShouldClose(m_Window);
	}
	void Window::SwapBuffers() const noexcept
	{
		 glfwSwapBuffers(m_Window);
	}
	void Window::PollEvents() noexcept
	{
		glfwPollEvents();
	}
	void Window::Clear(const float r, const float g, const float b, const float a) noexcept
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Window::RaiseEvent(Event& event)
	{
		if (m_Specs.callback) {
			m_Specs.callback(event);
		}
	}
}
