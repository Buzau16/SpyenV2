#pragma once
#include <print>
#include <optional>

#include <Window/Window.h>
#include <Renderer/Renderer.h>
#include <Core/Log.h>
#include <memory>


namespace Spyen {
	class Engine {
	public:
		Engine() = default;
		~Engine() = default;

		Engine(const WindowSpecifications& specs);

		void Run();

	private:
		std::shared_ptr<Window> m_Window;
		std::shared_ptr<Renderer> m_Renderer;
	};
}