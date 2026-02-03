#pragma once

#ifdef SP_RELEASE
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <Scene/Scene.h>
#include <Window/Window.h>
#include <Renderer/Renderer.h>
#include <memory>
#include <Physics/PhysicsEngine.h>
#include <Scene/SceneManager.h>
#include <Audio/AudioEngine.h>
#include <Events/Event.h>

namespace Spyen {

	// TODO: Refactor the quad tree to use the new entity system and the PhysicsEngine::OnUpdate function
	class Engine {
	public:
		Engine() = default;
		~Engine();

		explicit Engine(const uint32_t width, const uint32_t height, const std::string& title);

		void Run() const;
	private:

		void RaiseEvent(Event& event);
		// The order of these matters! Messing with the order might cause crashes or memory corruption
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<Renderer> m_Renderer = nullptr;
		std::unique_ptr<SceneManager> m_SceneManager = nullptr;
		//std::vector<Event&> m_EventQueue;
		friend class Director;
	};
}
