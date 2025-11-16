#include "Core.h"
#include <filesystem>


#include "AssetManager/IAssetManager.h"
#include "Physics/QuadTree.h"
#include "Scene/Components.h"
#include "Scene/Entity.h"
#include "Time/TimeStep.h"


namespace Spyen {

	constexpr float PhysicsStep = 1.0f / 60.f;

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
		if (IAssetManager::m_Instance)
		{
			IAssetManager::m_Instance = nullptr;
		}
	}

	void Engine::Run() const
	{
		SPY_CORE_ASSERT(m_ActiveScene, "Please create and set an active scene!");

		auto LastFrameTime = 0.0f;
		double accumulator = 0.0F;

		while (m_Window->IsOpen()) {
			m_Window->PollEvents();

			//glfwSwapInterval(0);

			m_Window->Clear(0.33f, 0.7f, 0.96f);

			const auto Time = static_cast<float>(glfwGetTime());
			Timestep TimeStep(Time - LastFrameTime);
			LastFrameTime = Time;

			accumulator += TimeStep;

			// Update physics at a fixed rate, independent of the fps / the rate that the game loop is running at
			while (accumulator >= PhysicsStep) {
				m_ActiveScene->GetEntityByName("test").GetComponent<RigidBodyComponent>().Velocity = { 100.0f, 0.0f };
				m_PhysicsEngine->Update(m_ActiveScene, { m_Window->GetWidth(), m_Window->GetHeight() }, PhysicsStep);
				accumulator -= PhysicsStep;
			}

			// Rendering
			m_Renderer->BeginFrame(m_ActiveScene->m_MainCamera.get());

			m_ActiveScene->OnRender(m_Renderer.get());

			m_Renderer->EndFrame();

			/*auto fps = 1.0f / TimeStep;
			SPY_CORE_INFO("FPS: {}", fps);*/

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
		scene->MakeSceneCamera({ m_Window->GetWidth() / 2, m_Window->GetHeight() / 2 }, { m_Window->GetWidth(), m_Window->GetHeight() });
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
		if (!scene->m_MainCamera)
		{
			scene->MakeSceneCamera({ m_Window->GetWidth() / 2, m_Window->GetHeight() / 2 }, { m_Window->GetWidth(), m_Window->GetHeight() });
		}
		return scene;
	}
}
