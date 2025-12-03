#pragma once
#include <Scene/Sprite.h>

class Player : public Spyen::Sprite
{
public:
	void OnInit() override;
	void OnUpdate(Spyen::Timestep dt) override;

	SP_CREATE_FUNC(Player);
};

