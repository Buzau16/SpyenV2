#pragma once
#include <vector>

#include "Scene/Entity.h"

namespace Spyen {
	class PhysicsEngine
	{
	public:
		PhysicsEngine() = default;
		~PhysicsEngine() = default;

		void AddEntity(Entity* entity);
		void Update(Scene* scene, float Timestep);
	private:
		std::vector<Entity*> m_Entities;
	};

}
