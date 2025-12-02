#pragma once
#include <memory>
#include <Time/TimeStep.h>
#include <Math/Math.h>
#include <Core/Defines.h>

namespace Spyen
{
	struct OBB {
		Vec2 Position = { 0, 0 };
		Vec2 HalfSize = { 0, 0 };
		float Rotation = 0.0f;

		OBB() = default;

		constexpr OBB(const Vec2& position, const Vec2& halfsize, const float rotation) :
			Position(position), HalfSize(halfsize), Rotation(rotation) {
		};
	};

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

		constexpr bool IsKinematic() const noexcept;
		void SetKinematic(const bool value) noexcept;

		constexpr bool IsCollidable() const noexcept;
		void SetCollidable(const bool value) noexcept;

		static std::unique_ptr<RigidBody> Create();

	protected:
		OBB Collider;
		Vec2 Velocity{ 0,0 };
		Vec2 Acceleration{ 0,0 };
		bool Kinematic = false;
		bool Collidable = true;
	};
}
