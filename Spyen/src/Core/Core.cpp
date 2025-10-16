#include "Core.h"
#include <filesystem>


namespace Spyen {
	Engine::Engine(const WindowSpecifications& specs)
	{
		Log::Init();
		SPY_CORE_INFO("{}", std::filesystem::current_path().string());
		m_Window = std::make_shared<Window>(specs);
		m_Renderer = std::make_shared<Renderer>("Shaders/QuadShader.vert", "Shaders/QuadShader.frag");
	}
	void Engine::Run()
	{
		glm::vec2 pos = { 0.0f, 0.0f };
		glm::vec3 color = { 1.0f, 1.0f, 1.0f };

		while (m_Window->IsOpen()) {
			m_Window->PollEvents();
			m_Window->Clear(0.3f, 0.5f, 0.8f);

			m_Renderer->BeginFrame();

			m_Renderer->DrawQuad(pos, color);

			m_Renderer->EndFrame();

			m_Window->SwapBuffers();
		}
	}
}
