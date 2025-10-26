#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "glm/glm.hpp"

namespace Spyen
{
	namespace Components
	{
		struct Transform
		{
			glm::vec2 Position = {0.0f, 0.0f};
			float Rotation = 0.0f;
			float Scale = 1.0f;

			Transform() = default;

			[[nodiscard]] glm::mat4 GetTransformMatrix() const noexcept
			{
				return glm::translate(glm::mat4(1.0f), glm::vec3(Position, 1.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(Scale, Scale, 1.0f));
			} 
		};


		struct Render
		{
			glm::vec3 Color = {0.0f, 0.0f, 0.0f};
			std::shared_ptr<Texture> Texture = nullptr;

			Render() = default;
			Render(const glm::vec3& color) : Color(color) {};
			Render(const std::shared_ptr<Spyen::Texture>& texture) : Texture(texture) {};


		};
	}
}
