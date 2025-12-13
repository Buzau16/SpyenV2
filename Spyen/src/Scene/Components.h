#pragma once
#include <memory>
#include <Time/TimeStep.h>
#include <Math/Math.h>
#include <Core/Defines.h>

namespace Spyen
{
	using OBB = Rectangle;

	class Node;

	class ScriptComponent {
	public:
		ScriptComponent() = default;
		virtual ~ScriptComponent();

		virtual void OnInit() {};
		virtual void OnUpdate(Timestep dt) {};

	protected:
		Node* Parent;
	private:
		friend class Node;
	};

	class RigidBody
	{
	public:
		RigidBody() = default;

		explicit RigidBody(const Vec2& position, const Vec2& scale, const float rotation);
		~RigidBody() = default;

		void OnUpdate(const Vec2& position, const Vec2& scale, const float rotation);

		SP_SYNTHESIZE(OBB, Collider, Collider);
		SP_SYNTHESIZE(Vec2, Velocity, Velocity);
		SP_SYNTHESIZE(Vec2, Acceleration, Acceleration);

		bool IsKinematic() const noexcept;
		void SetKinematic(const bool value) noexcept;

		bool IsCollidable() const noexcept;
		void SetCollidable(const bool value) noexcept;

		Node* GetParent() const noexcept;
		void SetParent(Node* node) noexcept;

		static std::unique_ptr<RigidBody> Create();

	protected:
		Node* Parent = nullptr;
		OBB Collider;
		Vec2 Velocity{ 0,0 };
		Vec2 Acceleration{ 0,0 };
		bool Kinematic = false;
		bool Collidable = true;
		friend class Node;
	};
}
