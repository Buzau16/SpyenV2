#pragma once
#include <array>
#include <utility>
#include <glm/glm.hpp>
#include <Math/Vector/Vec.h>
#include <Math/Primitives/Primitives.h>
#include <Math/Common.h>
#include <numbers>
#include <cstdint>

namespace Spyen
{	
	using OBB = Rectangle;
	namespace Math
	{
		// for converting degrees to radians mostly
		constexpr double PIDIV180 = std::numbers::pi / 180.0;

		// for common degree -> radian conversions

		// 30 degrees
		constexpr double PIDIV6 = std::numbers::pi / 6.0;
		// 45 degrees
		constexpr double PIDIV4 = std::numbers::pi / 4.0;
		// 60 degrees
		constexpr double PIDIV3 = std::numbers::pi / 3.0;
		// 90 degrees
		constexpr double PIDIV2 = std::numbers::pi / 2.0;
		// 180 degrees
		constexpr double PI = std::numbers::pi;
		// 270 degrees
		constexpr double PI3DIV2 = (std::numbers::pi * 3.0) / 2.0;
		// 360 degrees
		constexpr double PI2 = std::numbers::pi * 2.0;

		glm::vec2 ToGLMVec2(const Vec2& v);
		glm::vec3 ToGLMVec3(const Vec3& v);
		glm::ivec2 ToGLMIVec2(const IVec2& v);
		glm::ivec3 ToGLMIVec3(const IVec3& v);

		Vec2 ToSpyenVec2(const glm::vec2& v);
		Vec3 ToSpyenVec3(const glm::vec3& v);
		IVec2 ToSpyenIVec2(const glm::ivec2& v);
		IVec3 ToSpyenIVec3(const glm::ivec3& v);

		template<typename T>
			requires (std::is_arithmetic_v<T>&& std::is_floating_point_v<T>)
		constexpr const T Dot(const Vector2<T>& a, const Vector2<T>& b) noexcept{
			return a.x * b.x + a.y * b.y;
		}

		template<typename T>
			requires (std::is_arithmetic_v<T>&& std::is_floating_point_v<T>)
		constexpr const T Dot(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const T Cross(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			return a.x * b.y - a.y * b.x;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const Vector3<T> Cross(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			return {
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			};
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const T DistanceSq(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> d = a - b;
			return d.LengthSq();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const T DistanceSq(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			Vector3<T> d = a - b;
			return d.LengthSq();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		const T Distance(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> d = a - b;
			return d.Length();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		const T Distance(const Vector3<T>& a, const Vector3<T>& b) noexcept {
			Vector3<T> d = a - b;
			return d.Length();
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const T ToRadians(const T& degrees) noexcept{
			return degrees * static_cast<T>(0.01745329251994329576923690768489);
		}

		// TODO: Add refract

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const Vector2<T> Reflect(const Vector2<T>& incident, const Vector2<T>& axis) noexcept{
			return incident - (2.f * Dot(axis, incident) * axis);
		}

		// Return the angle between 2 vector as a unsigned float
		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const float AngleF(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> at;
			Vector2<T> bt;
			a.LengthSq() > 1 ? at = a.Normalize() : at = a;
			b.LengthSq() > 1 ? bt = b.Normalize() : bt = b;
			return std::acos(Clamp(Dot(at, bt), -1.f, 1.f));
		}

		// Return the angle between 2 vector as a signed float
		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const float AngleSF(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> at;
			Vector2<T> bt;
			a.LengthSq() > 1 ? at = a.Normalize() : at = a;
			b.LengthSq() > 1 ? bt = b.Normalize() : bt = b;
			return std::atan2(Cross(at, bt), Dot(at, bt));
		}

		// Return the angle between 2 vector as a unsigned double
		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const double AngleD(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> at;
			Vector2<T> bt;
			a.LengthSq() > 1 ? at = a.Normalize() : at = a;
			b.LengthSq() > 1 ? bt = b.Normalize() : bt = b;
			return std::acos(Clamp(Dot(at, bt), -1.f, 1.f));
		}

		// Return the angle between 2 vector as a signed double
		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const double AngleSD(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> at;
			Vector2<T> bt;
			a.LengthSq() > 1 ? at = a.Normalize() : at = a;
			b.LengthSq() > 1 ? bt = b.Normalize() : bt = b;
			return std::atan2(Cross(at, bt), Dot(at, bt));
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const T Lerp(const T& a, const T& b, const T& t) noexcept {
			return a + (b - a) * t;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const Vector2<T> Lerp(const Vector2<T>& a, const Vector2<T>& b, const T& t) noexcept {
			return Vector2<T>{
				Lerp(a.x, b.x, t),
				Lerp(a.y, b.y, t)
			};
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const Vector3<T> Lerp(const Vector3<T>& a, const Vector3<T>& b, const T& t) noexcept {
			return Vector3<T>{
				Lerp(a.x, b.x, t),
				Lerp(a.y, b.y, t),
				Lerp(a.z, b.z, t)
			};
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const Vector2<T> Min(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> vec;
			vec.x = Math::Min(a.x, b.x);
			vec.y = Math::Min(a.y, b.y);
			return vec;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr const Vector2<T> Max(const Vector2<T>& a, const Vector2<T>& b) noexcept {
			Vector2<T> vec;
			vec.x = Math::Max(a.x, b.x);
			vec.y = Math::Max(a.y, b.y);
			return vec;
		}

		constexpr std::pair<float, float> Project(const OBB& box, const Vec2& boxAxisX, const Vec2& boxAxisY, const Vec2& axis) {
			std::array<Vec2, 4> corners = {
			Vec2{box.Position + boxAxisX * box.Scale.x + boxAxisY * box.Scale.y},
			Vec2{box.Position - boxAxisX * box.Scale.x + boxAxisY * box.Scale.y},
			Vec2{box.Position - boxAxisX * box.Scale.x - boxAxisY * box.Scale.y},
			Vec2{box.Position + boxAxisX * box.Scale.x - boxAxisY * box.Scale.y}
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
		};

		bool IsColliding(const OBB& a, const OBB& b);
	}
}
