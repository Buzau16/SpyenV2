#pragma once
#include <Time/TimeStep.h>
#include <Scene/Entity.h>

namespace Spyen {
	class ScriptEngine
	{
	public:
		static void InitializeScript(Entity& entity);
		static void InvokeOnCreate(Entity& entity);
		static void InvokeOnUpdate(Entity& entity, Timestep ts);
		static void InvokeOnEvent(Entity& entity, Event& event);
		static void CleanupScript(Entity& entity);
	private:

	};

}

