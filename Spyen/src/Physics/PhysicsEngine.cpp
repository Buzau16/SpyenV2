#include "spypch.h"
#include "PhysicsEngine.h"

#include "QuadTree.h"
#include "Scene/Components.h"
#include "Math/Math.h"
#include <AssetManager/IAssetManager.h>
#include <Core/Director.h>
#include <Events/EntityEvents.h>


namespace Spyen
{
	void PhysicsEngine::ResolveCollisions(Spyen::Scene* scene, Spyen::QuadTree& tree)
	{
		auto collidable_objects = scene->GetEntitiesWith<TransformComponent, BoxColliderComponent>();
		Boundary object_search_boundary = {};
		int32_t search_offset = 256;

		for (const auto& [entity, tc, bcc] : collidable_objects.each()) {
			// possible bug
			ColliderEntity ce;
			ce.entity = entity;
			ce.ColliderPos = tc.Position + bcc.Offset;
			ce.ColliderScale = tc.Scale * bcc.Offset;
			ce.ColliderRotation = tc.Rotation + bcc.Rotation;
			tree.Insert(ce);
		}

		for (const auto& [entity, tc, bcc] : collidable_objects.each()) {
			object_search_boundary = { tc.Position.x, tc.Position.y, tc.Position.x + tc.Scale.x + search_offset, tc.Position.y + tc.Scale.y + search_offset };
			auto possible_collisions = tree.Query(object_search_boundary);

			for (auto& other : possible_collisions) {
				if (other.entity == entity) {
					continue;
				}

				OBB st = OBB({ tc.Position + bcc.Offset }, { tc.Scale * bcc.Scale }, tc.Rotation + bcc.Rotation);
				OBB nd = OBB(other.ColliderPos, other.ColliderScale, other.ColliderRotation);

				if (Spyen::Math::IsColliding(st, nd)) {
					// a bit scuffed
					Entity e = { entity, Director::GetActiveScene() };
					Entity r = { other.entity, Director::GetActiveScene() };
					EntityHitEvent event{ e,r };
					Director::RaiseEvent(event);
				}
			}
		}
	}
	void PhysicsEngine::UpdateRigidBodies(Spyen::Scene* scene, QuadTree& tree, double ts)
	{
		auto view = scene->GetEntitiesWith<TransformComponent, RigidBodyComponent>();
		for (auto [entity, tc, rbc] : view.each()) {
			switch (rbc.Type) {
				case RigidBodyComponent::BodyType::Static: break;
				case RigidBodyComponent::BodyType::Dynamic: {
					rbc.Velocity += rbc.Acceleration * ts;
					tc.Position += rbc.Velocity * ts;
					break;
				}
				case RigidBodyComponent::BodyType::Kinematic: break;
			}
		}
	}
	// todo: run this on another thread
	void PhysicsEngine::Update(Scene* scene,const glm::vec2& dimensions, double Timestep)
	{
		auto tree = QuadTree({ dimensions.x / 2, dimensions.y / 2, dimensions.x, dimensions.y }, 8);
		ResolveCollisions(scene, tree);
		UpdateRigidBodies(scene, tree, Timestep);
	}
}
