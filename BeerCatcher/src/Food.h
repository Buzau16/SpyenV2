#pragma once
#include <Scene/Sprite.h>
#include <Events/NodeEvents.h>

class Food : public Spyen::Sprite
{
public:
	void OnInit() override;
	/*void OnEvent(Spyen::Event& event) override;
	void OnUpdate(Spyen::Timestep dt) override;
	bool DestroySelf(Spyen::NodeHitEvent e);*/
	SP_CREATE_FUNC(Food);
private:
};

