#pragma once
#include <Scene/Node.h>
#include <Events/Event.h>
#include <Events/NodeEvents.h>

class TransitionScript : public Spyen::Node
{
public:
	void OnUpdate(Spyen::Timestep dt) override;
};

