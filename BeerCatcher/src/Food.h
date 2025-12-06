#pragma once
#include <Scene/Sprite.h>
#include <Events/NodeEvents.h>

class Food : public Spyen::Sprite
{
public:
	void OnInit() override;
	SP_CREATE_FUNC(Food);
private:
};

