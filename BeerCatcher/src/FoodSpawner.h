#pragma once
#include <Scene/Node.h>
#include <Events/Event.h>
#include <Events/NodeEvents.h>

class FoodSpawner : public Spyen::Node
{
public:
	void OnInit() override;
	void OnUpdate(Spyen::Timestep dt) override;
	void OnEvent(Spyen::Event& event) override;
	void SpawnFood();

	SP_CREATE_FUNC(FoodSpawner);
private:
	bool OnFoodEaten(Spyen::NodeHitEvent& event);
};

