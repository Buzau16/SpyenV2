#include "TransitionScript.h"
#include <Core/Director.h>
#include <Input/Input.h>

void TransitionScript::OnUpdate(Spyen::Timestep dt)
{
	if(Spyen::Input::IsKeyDown(Spyen::Key::Space))
		Spyen::Director::SetActiveScene("main");
}
