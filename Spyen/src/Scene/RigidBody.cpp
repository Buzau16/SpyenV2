#include "RigidBody.h"

namespace Spyen {
	RigidBody::RigidBody(const glm::vec2& position, const glm::vec2& scale, const float rotation) : 
		Collider(position, glm::vec2{scale.x / 2, scale.y / 2}, rotation)
	{}

	void RigidBody::OnUpdate(const glm::vec2& position, const glm::vec2& scale, const float rotation)
	{
		if (Collidable) {
			//Update the OBB
			Collider.Position = position;
			Collider.HalfSize = glm::vec2{ scale.x / 2, scale.y / 2 };
			Collider.Rotation = rotation;
		}
	}
	std::unique_ptr<RigidBody> RigidBody::Create()
	{
		return std::make_unique<RigidBody>();
	}
	constexpr bool RigidBody::IsKinematic() const noexcept
	{
		return Kinematic;
	}
	void RigidBody::SetKinematic(const bool value) noexcept
	{
		Kinematic = value;
	}
	constexpr bool RigidBody::IsCollidable() const noexcept
	{
		return Collidable;
	}
	void RigidBody::SetCollidable(const bool value) noexcept
	{
	}
}