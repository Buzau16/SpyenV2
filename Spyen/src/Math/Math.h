#pragma once
#include <array>
#include <utility>
#include <glm/glm.hpp>
#include <Math/Vector/Vec.h>

namespace Spyen
{	

	using Vec2 = Vector2<float>;
	using IVec2 = Vector2<int64_t>;
	using UVec2 = Vector2<uint64_t>;
	using Vec3 = Vector3<float>;
	using IVec3 = Vector3<int64_t>;
	using UVec3 = Vector3<uint64_t>;

struct OBB;
	namespace Math
	{
		glm::vec2 ToGLMVec2(const Vec2& v);
		glm::vec3 ToGLMVec3(const Vec3& v);
		glm::ivec2 ToGLMIVec2(const IVec2& v);
		glm::ivec3 ToGLMIVec3(const IVec3& v);

		template<typename T>
			requires (std::is_arithmetic_v<T>&& std::is_floating_point_v<T>)
		constexpr T Dot(const Vector2<T>& a, const Vector2<T>& b) noexcept{
			return a.x * b.x + a.y * b.y;
		}

		template<typename T>
			requires (std::is_arithmetic_v<T>&& std::is_floating_point_v<T>)
		constexpr T Dot(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr T Cross(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			return a.x * b.y - a.y * b.x;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr Vector3<T> Cross(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			return {
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			};
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr T DistanceSq(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			return a.LengthSq() - b.LengthSq();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr T DistanceSq(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			return a.LengthSq() - b.LengthSq();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		T Distance(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			return a.Length() - b.Length();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		T Distance(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			return a.Length() - b.Length();
		}

		std::pair<float, float> Project(const OBB& box, const Vec2& axis);
		bool IsColliding(const OBB& a, const OBB& b);
	}
}
