#include "spypch.h"
#include "PhysicsEngine.h"

#include "QuadTree.h"
#include "Scene/Components.h"
#include "Math/Math.h"
#include <AssetManager/IAssetManager.h>


namespace Spyen
{
	void PhysicsEngine::Update(Scene* scene,const glm::vec2& dimensions, double Timestep)
	{
		// update each object from a scene
		// to be implemented
		auto tree = QuadTree({dimensions.x / 2,dimensions.y / 2, dimensions.x, dimensions.y}, 8);
		//auto objects = scene->GetNodeGraph().GetRigidBodies();
		//Boundary object_search_boundary = {};
		//auto objects = scene->GetEntitiesWith<TransformComponent, RigidBodyComponent, ColliderComponent>();
		//Boundary object_search_boundary = {};
		//int32_t search_offset = 256;

		//// Insert the entities in the quad tree
		//for (const auto& [entity, trc, rbc, cc] : objects.each())
		//{
		//	tree.Insert(cc.OBB);
		//}

		//for (auto [entity, trc, rbc, cc] : objects.each())
		//{
		//	// Compute each object for collision
		//	object_search_boundary = {trc.Position.x, trc.Position.y, trc.Position.x + trc.Scale.x + search_offset, trc.Position.y + trc.Scale.y + search_offset };
		//	auto possible_collisions = tree.Query(object_search_boundary);
		//	for (auto& collider : possible_collisions)
		//	{
		//		// Compute the collision
		//		if (cc.OBB.Position == collider.Position)
		//			continue;

		//		if (Spyen::Math::IsColliding(cc.OBB, collider))
		//		{
		//			SPY_CORE_INFO("Collision detected!");
		//		}
		//	}

		//	// Update Non-Kinematic entities
		//	if (!rbc.IsKinematic)
		//	{
		//		rbc.Velocity += glm::vec2{ rbc.Acceleration.x * Timestep, rbc.Acceleration.y * Timestep };
		//		trc.Position += glm::vec2{ rbc.Velocity.x * Timestep, rbc.Velocity.y * Timestep };
		//	}

		//	// Update OBBs
		//	cc.OBB.Position = trc.Position;
		//	cc.OBB.Rotation = trc.Rotation;
		//	cc.OBB.HalfSize = { trc.Scale.x / 2, trc.Scale.y / 2 };
		//}
	}
}
