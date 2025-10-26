#pragma once
#include <print>

#include <Window/Window.h>
#include <Renderer/Renderer.h>
#include <memory>


namespace Spyen {
	class Engine {
	public:
		Engine() = default;
		~Engine() = default;

		explicit Engine(const WindowSpecifications& specs);

		void Run() const;

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
	};
}