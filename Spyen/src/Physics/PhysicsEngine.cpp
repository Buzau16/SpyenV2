#include "PhysicsEngine.h"

#include "Scene/Components.h"


namespace Spyen
{
	void PhysicsEngine::AddEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void PhysicsEngine::Update(Scene* scene, float Timestep)
	{
		// update each object from a scene
		auto objects = scene->GetEntitiesWith<TransformComponent, RigidBodyComponent>();

		for (auto [entity, trc, rbc]: objects.each())
		{
			// Update Non-Kinematic entities
			if (!rbc.IsKinematic)
			{
				rbc.Velocity += rbc.Acceleration * Timestep;
				trc.Position += rbc.Velocity * Timestep;
			}
		}
		// Compute each object for collision
	}
}
