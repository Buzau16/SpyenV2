#include "spypch.h"
#include "math.h"

#include <glm/glm.hpp>
#include <Scene/Components.h>

glm::vec2 Spyen::Math::ToGLMVec2(const Vec2& v)
{
	return glm::vec2(v.x, v.y);
}

glm::vec3 Spyen::Math::ToGLMVec3(const Vec3& v)
{
	return glm::vec3(v.x, v.y, v.z);
}

glm::ivec2 Spyen::Math::ToGLMIVec2(const IVec2& v)
{
	return glm::ivec2(v.x, v.y);
}

glm::ivec3 Spyen::Math::ToGLMIVec3(const IVec3& v)
{
	return glm::ivec3(v.x, v.y, v.z);
}

std::pair<float, float> Spyen::Math::Project(const OBB& box, const Vec2& axis)
{
	{
		Vec2 boxAxisX = { cos(box.Rotation), sin(box.Rotation) };
		Vec2 boxAxisY = { -sin(box.Rotation), cos(box.Rotation) };

		std::array<Vec2, 4> corners = {
			Vec2{box.Position + boxAxisX * box.HalfSize.x + boxAxisY * box.HalfSize.y},
			Vec2{box.Position - boxAxisX * box.HalfSize.x + boxAxisY * box.HalfSize.y},
			Vec2{box.Position - boxAxisX * box.HalfSize.x - boxAxisY * box.HalfSize.y},
			Vec2{box.Position + boxAxisX * box.HalfSize.x - boxAxisY * box.HalfSize.y}
		};

		float min = Dot(corners[0], axis);
		float max = min;

		for (int i = 1; i < 4; i++)
		{
			float p = Dot(corners[i], axis);
			min = std::min(p, min);
			max = std::max(p, max);
		}

		return std::make_pair(min, max);
	}
}

bool Spyen::Math::IsColliding(const OBB& a, const OBB& b)
{
	// get the axis of each object
	std::array<Vec2, 4> axes = {
		// a axis:
		Vec2{cos(a.Rotation), sin(a.Rotation)},
		Vec2{-sin(a.Rotation), cos(a.Rotation)},

		// b axis:
		Vec2{cos(b.Rotation), sin(b.Rotation)},
		Vec2{-sin(b.Rotation), cos(b.Rotation)}
	};

	for (const auto& axis : axes)
	{
		auto [minA, maxA] = Project(a, axis.Normalize());
		auto [minB, maxB] = Project(b, axis.Normalize());

		if (maxA < minB || maxB < minA)
			return false;
	}

	return true;
}
