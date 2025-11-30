#include "Sprite.h"
#include <Renderer/Renderer.h>

void Spyen::Sprite::OnInit()
{
	Node::OnInit();
}

void Spyen::Sprite::OnUpdate(Timestep dt)
{
	Node::OnUpdate(dt);
}

void Spyen::Sprite::OnRender(Renderer* renderer)
{
	if (Sprite::Texture) {
		renderer->DrawQuad(Position, Scale, Rotation, Sprite::Texture);
	}
	else {
		renderer->DrawQuad(Position, Scale, Rotation, Color);
	}
	
}
