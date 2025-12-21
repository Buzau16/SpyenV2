#pragma once
#include <unordered_map>
#include <Scene/Scene.h>

namespace Spyen {
	class SceneManager
	{
	public:
		SceneManager() = default;
		~SceneManager() = default;

		void AddScene(const std::string& name, std::unique_ptr<Scene> scene);
		void Transition(const std::string& name);
		Scene* GetActiveScene() { return m_ActiveScene; };


	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_SceneMap;
		Scene* m_ActiveScene = nullptr;
	};

}

