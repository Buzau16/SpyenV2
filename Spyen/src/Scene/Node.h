#pragma once
#include "Components.h"
#include <Time/TimeStep.h>

namespace Spyen {
	class Renderer;

	class Node
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		virtual void OnInit();
		virtual void OnUpdate(Timestep dt);
		virtual void OnRender(Renderer* renderer) {};

		constexpr glm::vec2 GetPosition() const noexcept;
		void SetPosition(const glm::vec2& position) noexcept;

		constexpr glm::vec2 GetScale() const noexcept;
		void SetScale(const glm::vec2& scale) noexcept;

		constexpr float GetRotation() const noexcept;
		void SetRotation(const float rotation) noexcept;

		constexpr OBB GetOBB() const noexcept;
		void SetOBB(const OBB& obb) noexcept;

		constexpr glm::vec2 GetVelocity() const noexcept;
		void SetVelocity(const glm::vec2& position) noexcept;

		constexpr glm::vec2 GetAcceleration() const noexcept;
		void SetAcceleration(const glm::vec2& scale) noexcept;


		// to be implemented
		void AddChild();


	private:
		std::vector<std::unique_ptr<Node>> m_Children;
	protected:
		OBB Collider;
		glm::vec2 Position{ 0,0 };
		glm::vec2 Scale{ 0,0 };
		glm::vec2 Velocity{ 0,0 };
		glm::vec2 Acceleration{ 0,0 };
		float Rotation = 0.f;
	private:
		Node* m_Parent = nullptr;
	protected:
		bool IsKinematic = false;
		bool Collidable = true;
	};


}
