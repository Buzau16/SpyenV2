#pragma once
#include <Time/TimeStep.h>
#include <Scene/Entity.h>

namespace Spyen {
	class ScriptEngine
	{
	public:
		static void InvokeOnCreate(Entity& entity);
		static void InvokeOnUpdate(Entity& entity, Timestep ts);
	private:

	};

}

