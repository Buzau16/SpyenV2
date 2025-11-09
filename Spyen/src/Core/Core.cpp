#include "Core.h"
#include <filesystem>


#include "AssetManager/IAssetManager.h"
#include "Physics/QuadTree.h"
#include "Scene/Components.h"
#include "Scene/Entity.h" 


namespace Spyen {
	

	Engine::Engine(const WindowSpecifications& specs)
	{
		Log::Init();
		SPY_CORE_INFO("Working directory: {}", std::filesystem::current_path().string());
		m_Window = std::make_unique<Window>(specs);
		m_Renderer = std::make_unique<Renderer>();
		m_AssetManager = std::make_unique<AssetManager>();
		IAssetManager::m_Instance = m_AssetManager.get();
		m_PhysicsEngine = std::make_unique<PhysicsEngine>();
	}

	Engine::~Engine()
	{
		IAssetManager::m_Instance = nullptr;
	}

	void Engine::Run() const
	{
		SPY_CORE_ASSERT(m_ActiveScene, "Please create and set an active scene!");

		auto LastFrameTime = 0.0f;

		
		
		while (m_Window->IsOpen()) {
			m_Window->PollEvents();

			m_Window->Clear(0.33f, 0.7f, 0.96f);

			const auto Time = static_cast<float>(glfwGetTime());
			Timestep TimeStep(Time - LastFrameTime);
			LastFrameTime = Time;

			m_Renderer->BeginFrame();

			m_ActiveScene->GetEntityByName("test").GetComponent<RigidBodyComponent>().Velocity = { 0.0f, 100.0f };

			m_PhysicsEngine->Update(m_ActiveScene, TimeStep);
			m_ActiveScene->OnRender(m_Renderer.get());

			QuadTree tree({ 640,360, m_Window->GetWidth(), m_Window->GetHeight() }, 4);
			for (uint32_t y : std::ranges::iota_view(0, 1000))
			{
				tree.Insert(Point{ static_cast<uint32_t>(rand() % 1280) , static_cast<uint32_t>(rand() % 720) });
			}

			m_Renderer->SetLineWidth(20.f);

			tree.Draw(m_Renderer.get());

			m_Renderer->EndFrame();

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
