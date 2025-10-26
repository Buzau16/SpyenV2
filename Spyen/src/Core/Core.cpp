#include "Core.h"
#include <filesystem>

#include "Scene/Components.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h" 


namespace Spyen {
	Engine::Engine(const WindowSpecifications& specs)
	{
		Log::Init();
		SPY_CORE_INFO("Working directory: {}", std::filesystem::current_path().string());
		m_Window = std::make_unique<Window>(specs);
		m_Renderer = std::make_unique<Renderer>("Shaders/QuadShader.vert", "Shaders/QuadShader.frag");
	}
	void Engine::Run() const
	{
		Scene scene;
		auto ent = scene.CreateEntity("test");
		ent->AddComponent<Components::Transform>();
		const auto& comp = ent->GetComponent<Components::Transform>();
		ent->AddComponent<Components::Render>();
		ent->GetComponent<Components::Render>().Texture = std::make_shared<Texture>("assets/textures/Box.png");

		while (m_Window->IsOpen()) {
			m_Window->PollEvents();

			m_Window->Clear(0.3f, 0.5f, 0.8f);

			scene.OnRender(m_Renderer.get());

			m_Window->SwapBuffers();
		}
	}
}
