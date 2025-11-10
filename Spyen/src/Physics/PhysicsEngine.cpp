#include "PhysicsEngine.h"

#include "QuadTree.h"
#include "Scene/Components.h"


namespace Spyen
{
	void PhysicsEngine::AddEntity(Entity* entity)
	{
		m_Entities.push_back(entity);
	}

	void PhysicsEngine::Update(Scene* scene,const glm::ivec2& dimensions, double Timestep)
	{
		// update each object from a scene
		auto tree = QuadTree({0,0, dimensions.x, dimensions.y}, 8);
		auto objects = scene->GetEntitiesWith<TransformComponent, RigidBodyComponent>();
		Boundary object_search_boundary = {};
		int32_t search_offset = 256;

		// Insert the entities in the quad tree
		for (const auto& [entity, trc, rbc] : objects.each())
		{
			tree.Insert({ trc.Position.x, trc.Position.y });
		}

		for (auto [entity, trc, rbc] : objects.each())
		{
			// Compute each object for collision
			// TODO: refactor this to use oriented bounding boxes
			object_search_boundary = {trc.Position.x, trc.Position.y, trc.Position.x + trc.Scale.x + search_offset, trc.Position.y + trc.Scale.y + search_offset };
			auto possible_coliisions = tree.Query(object_search_boundary);
			for (auto& center : possible_coliisions)
			{
				// Compute the collision
				if (trc.Position.x == center.x && trc.Position.y == center.y)
					continue;

				if (glm::distance(glm::vec2(center.x, center.y), { trc.Position.x, trc.Position.y }) < std::max(trc.Scale.x, trc.Scale.y)) {
					SPY_CORE_INFO("Collision detected!");
				}
			}

			// Update Non-Kinematic entities
			if (!rbc.IsKinematic)
			{
				rbc.Velocity += glm::vec2{ rbc.Acceleration.x * Timestep, rbc.Acceleration.y * Timestep };
				trc.Position += glm::vec2{ rbc.Velocity.x * Timestep, rbc.Velocity.y * Timestep };
			}
		}
	}
}
