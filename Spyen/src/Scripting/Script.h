#pragma once

#include <Scene/Entity.h>
#include <Time/TimeStep.h>

namespace Spyen {
	class Script
	{
	public:
		virtual ~Script() {};

		virtual void OnCreate() {};
		virtual void OnUpdate(Timestep ts) {};
	protected:
		// Helpers

		// Transform
		Vec2& GetPosition() noexcept { return m_Parent.GetComponent<TransformComponent>().Position; }
		Vec2& GetScale() noexcept { return m_Parent.GetComponent<TransformComponent>().Scale; };
		float& GetRotation() noexcept { return m_Parent.GetComponent<TransformComponent>().Rotation; };

		// RigidBody
		Vec2& GetVelocity() noexcept { return m_Parent.GetComponent<RigidBodyComponent>().Velocity;	}
		Vec2& GetAcceleration() noexcept { return m_Parent.GetComponent<RigidBodyComponent>().Acceleration; }

	private:
		Entity m_Parent;
		friend class Scene;
	};

}

