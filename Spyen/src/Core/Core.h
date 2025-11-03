#pragma once


#include "Scene/Scene.h"

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

		Scene* CreateScene(const std::string& name);
		Scene* CreateSceneA(const std::string& name);
		Scene* GetSceneByName(const std::string& name);
		Scene* GetSceneByNameA(const std::string& name);

		Scene* GetActiveScene() const { return m_ActiveScene; };

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene = nullptr;
	};
}
