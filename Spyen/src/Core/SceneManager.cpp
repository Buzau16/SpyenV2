#include "spypch.h"
#include "SceneManager.h"
#include <Core/Defines.h>
#include <Core/Log.h>


namespace Spyen {
	void SceneManager::AddScene(const std::string& name, std::unique_ptr<Scene> scene)
	{
		scene->OnInit();
		m_Scenes[name] = std::move(scene);
	}
	void SceneManager::SetActiveScene(const std::string& name)
	{
		if (!m_Scenes.contains(name)) {
			SPY_CORE_ERROR("Scene {} does not exist!");
			return;
		}
		m_ActiveScene = m_Scenes.at(name).get();
	}
	void SceneManager::Transition(const std::string& name)
	{
		if (!m_Scenes.contains(name)) {
			SPY_CORE_ERROR("Scene {} does not exist!");
			return;
		}
		m_ActiveScene = m_Scenes.at(name).get();
	}

	Scene* SceneManager::GetActiveScene() const noexcept
	{
		SPY_CORE_ASSERT(m_ActiveScene, "No active scene!");
		return m_ActiveScene;
	}

};
