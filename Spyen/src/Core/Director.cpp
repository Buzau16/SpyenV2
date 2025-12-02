#include "spypch.h"
#include "Director.h"

namespace Spyen {
	Engine* Director::s_Instance = nullptr;
	Vec2 Director::GetWindowDimensions()
	{
		return Vec2{ s_Instance->m_Window->GetWidth(), s_Instance->m_Window->GetHeight() };
	}
	Scene* Director::GetActiveScene()
	{
		return s_Instance->m_SceneManager->GetActiveScene();
	}

	void Director::SetActiveScene(const std::string& name)
	{
		return s_Instance->m_SceneManager->SetActiveScene(name);
	}

	void Director::AddScene(const std::string& name, std::unique_ptr<Scene> scene)
	{
		return s_Instance->m_SceneManager->AddScene(name, std::move(scene));
	}

	void Director::Transition(const std::string& name)
	{
		s_Instance->m_SceneManager->Transition(name);
	}
}