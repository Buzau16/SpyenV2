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
			float Scale = 1.0f;

			TransformComponent() = default;

			[[nodiscard]] glm::mat4 GetTransformMatrix() const noexcept
			{
				return glm::translate(glm::mat4(1.0f), glm::vec3(Position, 1.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(Scale, Scale, 1.0f));
			} 
		};


		struct RenderComponent
		{
			glm::vec3 Color = {0.0f, 0.0f, 0.0f};
			Spyen::Texture* Texture = nullptr;

			RenderComponent() = default;
			RenderComponent(const glm::vec3& color) : Color(color) {};
			RenderComponent(Spyen::Texture* texture) : Texture(texture) {};


		};
}
