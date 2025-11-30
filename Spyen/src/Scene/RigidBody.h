#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Components.h"
#include <Core/Defines.h>

namespace Spyen {
	class RigidBody
	{
	public:
		explicit RigidBody(const glm::vec2& position, const glm::vec2& scale, const float rotation);
		~RigidBody() = default;

		void OnUpdate(const glm::vec2& position, const glm::vec2& scale, const float rotation);

		SP_SYNTHESIZE(OBB, Collider, Collider);
		SP_SYNTHESIZE(glm::vec2, Velocity, Velocity);
		SP_SYNTHESIZE(glm::vec2, Acceleration, Acceleration);

		constexpr bool IsKinematic() const noexcept;
		void SetKinematic(const bool value) noexcept;

		constexpr bool IsCollidable() const noexcept;
		void SetCollidable(const bool value) noexcept;

		static std::unique_ptr<RigidBody> Create();

	protected:
		OBB Collider;
		glm::vec2 Velocity{ 0,0 };
		glm::vec2 Acceleration{ 0,0 };
		bool Kinematic = false;
		bool Collidable = true;
	};

}

