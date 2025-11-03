#include "Core.h"
#include <filesystem>


#include "Scene/Components.h"
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
		SPY_CORE_ASSERT(m_ActiveScene, "Please create and set an active scene!");

		while (m_Window->IsOpen()) {
			m_Window->PollEvents();

			m_Window->Clear(0.3f, 0.5f, 0.8f);

			m_ActiveScene->OnRender(m_Renderer.get());

			m_Window->SwapBuffers();
		}
	}

	Scene* Engine::CreateScene(const std::string& name)
	{
		SPY_CORE_ASSERT(!m_Scenes.contains(name), "Scene {} already exists!", name.c_str());
		m_Scenes.emplace(name, std::make_unique<Scene>());
		return m_Scenes.at(name).get();
	}

	Scene* Engine::CreateSceneA(const std::string& name)
	{
		SPY_CORE_ASSERT(!m_Scenes.contains(name), "Scene {} already exists!", name.c_str());
		m_Scenes.emplace(name, std::make_unique<Scene>());
		auto scene = m_Scenes.at(name).get();
		m_ActiveScene = scene;
		return scene;
	}

	Scene* Engine::GetSceneByName(const std::string& name)
	{
		SPY_CORE_ASSERT(m_Scenes.contains(name), "Scene {} doesn't exists!", name.c_str());
		return m_Scenes.at(name).get();
	}

	Scene* Engine::GetSceneByNameA(const std::string& name)
	{
		SPY_CORE_ASSERT(m_Scenes.contains(name), "Scene {} doesn't exists!", name.c_str());
		auto scene = m_Scenes.at(name).get();
		m_ActiveScene = scene;
		return scene;
	}
}
