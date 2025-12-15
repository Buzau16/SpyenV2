#include "spypch.h"
#include "SceneManager.h"
#include <Core/Log.h>

namespace Spyen {
	void SceneManager::AddScene(const std::string& name, Scene&& scene)
	{
		if (m_SceneMap.contains(name)) {
			SPY_CORE_ERROR("Scene {} already exists!", name.c_str());
			return;
		}
		m_SceneMap.emplace(std::move(name), std::move(scene));
	}
	void SceneManager::Transition(const std::string& name)
	{
		if (!m_SceneMap.contains(name)) {
			SPY_CORE_ERROR("Scene {} doesnt not exist!", name.c_str());
			return;
		}
		m_ActiveScene = &m_SceneMap.at(name);
	}
}