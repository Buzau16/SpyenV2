#include "spypch.h"
#include "Math.h"

#include <glm/glm.hpp>

namespace Spyen {

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

	Vec2 Math::ToSpyenVec2(const glm::vec2& v)
	{
		return Vec2(v.x, v.y);
	}

	Vec3 Math::ToSpyenVec3(const glm::vec3& v)
	{
		return Vec3(v.x, v.y, v.z);
	}

	IVec2 Math::ToSpyenIVec2(const glm::ivec2& v)
	{
		return IVec2(v.x, v.y);
	}

	IVec3 Math::ToSpyenIVec3(const glm::ivec3& v)
	{
		return IVec3(v.x, v.y, v.z);
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
			auto normAxis = axis.Normalize();
			auto [minA, maxA] = Project(a, axes[0], axes[1], normAxis);
			auto [minB, maxB] = Project(b, axes[2], axes[3], normAxis);

			if (maxA < minB || maxB < minA)
				return false;
		}

		return true;
	}
}


