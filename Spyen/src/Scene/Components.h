#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "glm/glm.hpp"
#include "Renderer/Texture.h"

namespace Spyen
{
		struct TransformComponent
		{
			glm::vec2 Position = {0.0f, 0.0f};
			float Rotation = 0.0f;
			glm::vec2 Scale = {100, 100};

			TransformComponent() = default;

			[[nodiscard]] glm::mat4 GetTransformMatrix() const noexcept
			{
				return glm::translate(glm::mat4(1.0f), glm::vec3(Position, 1.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(Scale.x, Scale.y, 1.0f));
			} 
		};


		struct RenderComponent
		{
			glm::vec3 Color = {0.0f, 0.0f, 0.0f};
			Spyen::Texture* Texture = nullptr;
			bool IsVisible = true;

			RenderComponent() = default;
			RenderComponent(const glm::vec3& color) : Color(color) {};
			RenderComponent(Spyen::Texture* texture) : Texture(texture) {};
		};


		// needed for other functions in other places
		struct OBB {
			glm::vec2 Position = { 0, 0 };
			glm::vec2 HalfSize = { 0, 0 };
			float Rotation = 0.0f;

			constexpr OBB(const glm::vec2& position, const glm::vec2& halfsize, const float rotation) :
				Position(position), HalfSize(halfsize), Rotation(rotation) {};
		};

		struct RigidBodyComponent
		{
			glm::vec2 Velocity = { 0,0 };
			glm::vec2 Acceleration = { 0,0 };
			bool IsKinematic = false;

			RigidBodyComponent() = default;
		};

		struct ColliderComponent
		{
			OBB OBB;

			ColliderComponent() = default;
			//ColliderComponent(const TransformComponent& comp) : OBB(comp), Projection({ 0,0 }) {}
		};
}
