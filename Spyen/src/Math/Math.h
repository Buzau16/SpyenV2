#pragma once
#include <array>
#include <glm/glm.hpp>
#include "Scene/Components.h"



namespace Spyen
{
	namespace Math
	{
		inline std::pair<float, float> Project(const OBB& box, const glm::vec2& axis)
		{
			glm::vec2 boxAxisX = { cos(box.Rotation), sin(box.Rotation) };
			glm::vec2 boxAxisY = { -sin(box.Rotation), cos(box.Rotation) };

			std::array<glm::vec2, 4> corners = {
				glm::vec2{box.Position + boxAxisX * box.HalfSize.x + boxAxisY * box.HalfSize.y},
				glm::vec2{box.Position - boxAxisX * box.HalfSize.x + boxAxisY * box.HalfSize.y},
				glm::vec2{box.Position - boxAxisX * box.HalfSize.x - boxAxisY * box.HalfSize.y},
				glm::vec2{box.Position + boxAxisX * box.HalfSize.x - boxAxisY * box.HalfSize.y}
			};

			float min = glm::dot(corners[0], axis);
			float max = min;

			for (int i = 1; i < 4; i++)
			{
				float p = glm::dot(corners[i], axis);
				min = std::min(p, min);
				max = std::max(p, max);
			}

			return std::make_pair(min, max);
		}

		inline bool IsColliding(const OBB& a, const OBB& b)
		{
			// get the axis of each object
			std::array<glm::vec2, 4> axes = {
				// a axis:
				glm::vec2{cos(a.Rotation), sin(a.Rotation)},
				glm::vec2{-sin(a.Rotation), cos(a.Rotation)},

				// b axis:
				glm::vec2{cos(b.Rotation), sin(b.Rotation)},
				glm::vec2{-sin(b.Rotation), cos(b.Rotation)}
			};

			for (const auto& axis : axes)
			{
				glm::vec2 na = glm::normalize(axis);

				auto [minA, maxA] = Project(a, na);
				auto [minB, maxB] = Project(b, na);

				if (maxA < minB || maxB < minA)
					return false;
			}

			return true;
		}
	}
}
