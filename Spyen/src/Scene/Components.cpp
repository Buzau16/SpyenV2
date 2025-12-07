#include "spypch.h"
#include "Components.h"
#include <Scene/Node.h>


namespace Spyen {
	RigidBody::RigidBody(const Vec2& position, const Vec2& scale, const float rotation) :
		Collider(position, scale / 2, rotation)
	{
	}

	void RigidBody::OnUpdate(const Vec2& position, const Vec2& scale, const float rotation)
	{
		if (Collidable) {
			//Update the OBB
			Collider.Position = position;
			Collider.Scale = scale / 2;
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
		Collidable = value;
	}

	Node* RigidBody::GetParent() const noexcept
	{
		return Parent;
	}

	void RigidBody::SetParent(Node* node) noexcept
	{
		Parent = node;
	}

	ScriptComponent::~ScriptComponent()
	{
		if (Parent) {
			Parent = nullptr;
		}
	}
}