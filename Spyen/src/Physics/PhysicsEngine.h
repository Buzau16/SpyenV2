#pragma once
#include <glm/glm.hpp>

namespace Spyen {
	class QuadTree;
	class Scene;

	class PhysicsEngine
	{
	public:
		PhysicsEngine() = default;
		~PhysicsEngine() = default;
		// maybe rewrite this
		static void Update(Scene* scene, const glm::vec2& dimensions, double Timestep);
	private:
		static void ResolveCollisions(Spyen::Scene* scene, Spyen::QuadTree& tree);
		static void UpdateRigidBodies(Spyen::Scene* scene, QuadTree& tree, double ts);
	};

}
