#pragma once

#ifdef SP_RELEASE
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Scene/Scene.h"

#include <Window/Window.h>
#include <Renderer/Renderer.h>
#include <memory>
#include "AssetManager/AssetManager.h"
#include "Physics/PhysicsEngine.h"
#include <Audio/AudioEngine.h>


// TODO: refactor the remaining physics engine update function, the run function and make some camera controller thing

namespace Spyen {
	class Engine {
	public:
		Engine() = default;
		~Engine();

		explicit Engine(const WindowSpecifications& specs);

		void Run() const;

		Scene* CreateScene(const std::string& name);
		Scene* CreateSceneA(const std::string& name);
		Scene* GetSceneByName(const std::string& name);
		Scene* GetSceneByNameA(const std::string& name);

		Scene* GetActiveScene() const { return m_ActiveScene; };

	private:
		// The order of these matters! Messing with the order might cause crashes or memory corruption
		std::unique_ptr<Window> m_Window = nullptr;
		std::unique_ptr<Renderer> m_Renderer = nullptr;
		std::unique_ptr<AudioEngine> m_AudioEngine = nullptr;
		std::unique_ptr<AssetManager> m_AssetManager = nullptr;
		std::unique_ptr<PhysicsEngine> m_PhysicsEngine = nullptr;
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene = nullptr;
	};
}
