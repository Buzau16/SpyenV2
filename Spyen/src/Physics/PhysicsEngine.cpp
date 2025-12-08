#include "spypch.h"
#include "PhysicsEngine.h"

#include "QuadTree.h"
#include "Scene/Components.h"
#include "Math/Math.h"
#include <AssetManager/IAssetManager.h>
#include <Core/Director.h>
#include <Events/NodeEvents.h>


namespace Spyen
{
	void PhysicsEngine::Update(Scene* scene,const glm::vec2& dimensions, double Timestep)
	{
		// update each object from a scene
		auto tree = QuadTree({dimensions.x / 2,dimensions.y / 2, dimensions.x, dimensions.y}, 8);
		auto rbs = scene->GetRigidBodies();
		auto nodes = scene->GetNodesWithRigidBodies();
		Boundary object_search_boundary = {};
		int32_t search_offset = 256;

		for (const auto& rb : rbs) {
			tree.Insert(rb);
		}

		for (auto& node : nodes) {
			auto c = node->GetRigidBody()->GetCollider();
			object_search_boundary = { c.Position.x, c.Position.y, c.Position.x + c.Scale.x + search_offset, c.Position.y + c.Scale.y + search_offset };
			auto possible_collisions = tree.Query(object_search_boundary);
			for (auto& rb : possible_collisions) {
				if (c.Position == rb.GetCollider().Position) {
					continue;
				}
				if (Spyen::Math::IsColliding(c, rb.GetCollider())) {
					SPY_CORE_INFO("Collision detected!");
					NodeHitEvent e(node, rb.GetParent());
					Director::RaiseEvent(e);
				}
			}
		}

	}
}
