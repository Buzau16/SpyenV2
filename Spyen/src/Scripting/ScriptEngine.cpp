#include "spypch.h"
#include "ScriptEngine.h"

#include <Scripting/Script.h>


namespace Spyen {
	void ScriptEngine::InitializeScript(Entity& entity)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->m_Parent = entity;
	}
	void ScriptEngine::InvokeOnCreate(Entity& entity)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->OnCreate();
	}

	void ScriptEngine::InvokeOnUpdate(Entity& entity, Timestep ts)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->OnUpdate(ts);
	}

	void ScriptEngine::InvokeOnEvent(Entity& entity, Event& event)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->OnEvent(event);
	}

	void ScriptEngine::CleanupScript(Entity& entity)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->m_Parent = Entity{};
	}

}
