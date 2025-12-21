#include "spypch.h"
#include "ScriptEngine.h"

#include <Scripting/Script.h>


namespace Spyen {
	void ScriptEngine::InvokeOnCreate(Entity& entity)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->OnCreate();
	}

	void ScriptEngine::InvokeOnUpdate(Entity& entity, Timestep ts)
	{
		entity.GetComponent<ScriptComponent>().ScriptInstance->OnUpdate(ts);
	}

}
