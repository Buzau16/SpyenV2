#pragma once
#include <vector>
#include <Scene/Scene.h>

namespace Spyen {
	class PhysicsEngine
	{
	public:
		PhysicsEngine() = default;
		~PhysicsEngine() = default;

		// maybe rewrite this
		void Update(Scene* scene, const glm::vec2& dimensions, double Timestep);
	private:
		//std::vector<Entity*> m_Entities;
	};

}
