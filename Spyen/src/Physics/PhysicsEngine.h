#pragma once
#include <vector>
#include <Scene/Scene.h>
#include <glm/glm.hpp>

namespace Spyen {
	class QuadTree;

	class PhysicsEngine
	{
	public:
		PhysicsEngine() = default;
		~PhysicsEngine() = default;
		// maybe rewrite this
		void Update(Scene* scene, const glm::vec2& dimensions, double Timestep);
	private:
		void ResolveCollisions(Spyen::Scene* scene, Spyen::QuadTree& tree);
		void UpdateRigidBodies(Spyen::Scene* scene, QuadTree& tree, double ts);
	};

}
