#include "spypch.h"
#include "Core.h"
#include <filesystem>


#include "AssetManager/IAssetManager.h"
#include "Physics/QuadTree.h"
#include "Scene/Components.h"
#include "Time/TimeStep.h"
#include <Audio/IAudioEngine.h>
#include <Core/Director.h>
#include <GLFW/glfw3.h>

namespace Spyen {

	// TODO: Add scripting/systems and events

	constexpr float PhysicsStep = 1.0f / 60.f;

	Engine::Engine(const uint32_t width, const uint32_t height, const std::string& title)
	{
		WindowSpecifications specs{
			.Width = width,
			.Height = height,
			.Title = title,
			.callback = [this](Event& event) {RaiseEvent(event); }
		};
		Log::Init();
		SPY_CORE_INFO("Working directory: {}", std::filesystem::current_path().string());
		m_Window = std::make_unique<Window>(specs);
		m_Renderer = std::make_unique<Renderer>();
		m_AudioEngine = std::make_unique<AudioEngine>();
		IAudioEngine::s_Engine = m_AudioEngine.get();
		m_AssetManager = std::make_unique<AssetManager>();
		IAssetManager::s_Instance = m_AssetManager.get();
		m_PhysicsEngine = std::make_unique<PhysicsEngine>();
		m_SceneManager = std::make_unique<SceneManager>();
		Director::s_Instance = this;
	}

	Engine::~Engine()
	{
		if (IAssetManager::s_Instance)
		{
			IAssetManager::s_Instance = nullptr;
		}
		if (IAudioEngine::s_Engine)
		{
			IAudioEngine::s_Engine = nullptr;
		}
		if (Director::s_Instance) {
			Director::s_Instance = nullptr;
		}
	}

	void Engine::Run() const
	{
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

			// look into this as it makes the game engine run painfully slow at a high amount of objects clumped together
			// Update physics at a fixed rate, independent of the fps / the rate that the game loop is running at
			while (accumulator >= PhysicsStep) {
				m_PhysicsEngine->Update(m_SceneManager->GetActiveScene(), {m_Window->GetWidth(), m_Window->GetHeight()}, PhysicsStep);
				accumulator -= PhysicsStep;
			}

			
			m_SceneManager->GetActiveScene()->OnUpdate(TimeStep);

			// Rendering
			m_SceneManager->GetActiveScene()->OnRender(m_Renderer.get(), m_Window->GetWidth(), m_Window->GetHeight());

			/*auto fps = 1.0f / TimeStep;
			SPY_CORE_INFO("FPS: {}", fps);*/

			m_Window->SwapBuffers();
		}
	}
	void Engine::RaiseEvent(Event& event)
	{
		m_SceneManager->GetActiveScene()->OnEvent(event);
	}
}
