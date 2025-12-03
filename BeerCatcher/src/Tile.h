#pragma once
#include <Scene/Sprite.h>
#include <Core/Defines.h>

class Tile : public Spyen::Sprite
{
public:
	void OnInit() override;
	//void OnUpdate(Spyen::Timestep dt) override;

	SP_CREATE_FUNC(Tile);
};

