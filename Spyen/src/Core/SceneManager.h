#pragma once
#include <unordered_map>
#include <memory>
#include "Scene/Scene.h"

namespace Spyen {
	class SceneManager
	{
	public:
		SceneManager() = default;
		~SceneManager() = default;

		void AddScene(const std::string& name, std::unique_ptr<Scene> scene);
		void SetActiveScene(const std::string& name);
		void Transition(const std::string& name);
		Scene* GetActiveScene() const noexcept;

	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
		Scene* m_ActiveScene = nullptr;
	};

}

