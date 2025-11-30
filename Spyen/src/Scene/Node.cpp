#include "Node.h"

void Spyen::Node::OnInit()
{
	if (Collidable) {
		//Create the OBB
		Collider.Position = Position;
		Collider.HalfSize = glm::vec2{ Scale.x / 2, Scale.y / 2 };
		Collider.Rotation = Rotation;
	}
}

void Spyen::Node::OnUpdate(Timestep dt)
{
	if (Collidable) {
		//Update the OBB
		Collider.Position = Position;
		Collider.HalfSize = glm::vec2{ Scale.x / 2, Scale.y / 2 };
		Collider.Rotation = Rotation;
	}
}
