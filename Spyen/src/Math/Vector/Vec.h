#pragma once
#include <type_traits>
#include <cmath>
#include <Core/Log.h>

namespace Spyen {
	template<typename T>
	requires(std::is_arithmetic_v<T>)
	struct Vector2 {
		T x, y;

		constexpr Vector2() : x(0), y(0) {};

		// Universal type construtor :)
		template<typename X, typename Y>
			requires (std::is_arithmetic_v<X>&& std::is_arithmetic_v<Y>)
		constexpr Vector2(X xx, Y yy)
			: x(static_cast<T>(xx)), y(static_cast<T>(yy)) {
		}
		template<typename XY>
			requires (std::is_arithmetic_v<XY>)
		constexpr Vector2(XY xxyy)
			: x(static_cast<T>(xxyy)), y(static_cast<T>(xxyy)) {
		}

		constexpr Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y;	return *this; }
		constexpr Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y;	return *this; }
		constexpr Vector2& operator*=(const Vector2& other) { x *= other.x; y *= other.y;	return *this; }
		constexpr Vector2& operator/=(const Vector2& other) { x /= other.x; y /= other.y;	return *this; }

		constexpr Vector2& operator+=(const T s) { x += s; y += s;	return *this; }
		constexpr Vector2& operator-=(const T s) { x -= s; y -= s;	return *this; }
		constexpr Vector2& operator*=(const T s) { x *= s; y *= s;	return *this; }
		constexpr Vector2& operator/=(const T s) { x /= s; y /= s;	return *this; }

		constexpr Vector2 operator+(const Vector2& other) const { return Vector2{ x + other.x, y + other.y }; }
		constexpr Vector2 operator-(const Vector2& other) const { return Vector2{ x - other.x, y - other.y }; }
		constexpr Vector2 operator*(const Vector2& other) const { return Vector2{ x * other.x, y * other.y }; }
		constexpr Vector2 operator/(const Vector2& other) const { return Vector2{ x / other.x, y / other.y }; }

		constexpr Vector2 operator+(const T s) const { return Vector2{ x + s, y + s }; }
		constexpr Vector2 operator-(const T s) const { return Vector2{ x - s, y - s }; }
		constexpr Vector2 operator*(const T s) const { return Vector2{ x * s, y * s }; }
		constexpr Vector2 operator/(const T s) const { return Vector2{ x / s, y / s }; }

		constexpr bool operator==(const Vector2& o) const { return x == o.x && y == o.y; }
		constexpr bool operator!=(const Vector2& o) const { return !(*this == o); }

		constexpr T LengthSq() const noexcept{
			return x * x + y * y;
		}

		T Length() const noexcept{ 
			if constexpr (std::is_floating_point_v<T>) {
				return std::sqrt(x*x + y*y);
			}
			else {
				return static_cast<T>(std::sqrt(static_cast<double>(LengthSq())));
			}
		};

		constexpr Vector2 Normalize() const requires std::is_floating_point_v<T>{ 
			T len = Length();
			SPY_CORE_ASSERT(len > 0, "Length is 0!");
			return Vector2{ x / len, y / len };
		};
	};

	template<typename T>
	requires(std::is_arithmetic_v<T>)
	struct Vector3 {
		T x, y, z;

		constexpr Vector3() : x(0), y(0), z(0) {};

		// Universal type construtor :)
		template<typename X, typename Y, typename Z>
			requires (std::is_arithmetic_v<X>&& std::is_arithmetic_v<Y>&& std::is_arithmetic_v<Z>)
		constexpr Vector3(X xx, Y yy, Z zz)
			: x(static_cast<T>(xx)), y(static_cast<T>(yy)), z(static_cast<T>(zz)) {
		}
		template<typename XYZ>
			requires (std::is_arithmetic_v<XYZ>)
		constexpr Vector3(XYZ xxyyzz)
			: x(static_cast<T>(xxyyzz)), y(static_cast<T>(xxyyzz)), z(static_cast<T>(xxyyzz)) {
		}

		constexpr Vector3& operator+=(const Vector3& other) { x += other.x; y += other.y; z += other.z; return *this; }
		constexpr Vector3& operator-=(const Vector3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		constexpr Vector3& operator*=(const Vector3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		constexpr Vector3& operator/=(const Vector3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

		constexpr Vector3& operator+=(const T s) { x += s; y += s;	z += s; return *this; }
		constexpr Vector3& operator-=(const T s) { x -= s; y -= s;	z -= s; return *this; }
		constexpr Vector3& operator*=(const T s) { x *= s; y *= s;	z *= s; return *this; }
		constexpr Vector3& operator/=(const T s) { x /= s; y /= s;	z /= s; return *this; }

		constexpr Vector3 operator+(const Vector3& other) const { return Vector3{ x + other.x, y + other.y, z + other.z }; }
		constexpr Vector3 operator-(const Vector3& other) const { return Vector3{ x - other.x, y - other.y, z - other.z }; }
		constexpr Vector3 operator*(const Vector3& other) const { return Vector3{ x * other.x, y * other.y, z * other.z }; }
		constexpr Vector3 operator/(const Vector3& other) const { return Vector3{ x / other.x, y / other.y, z / other.z }; }

		constexpr Vector3 operator+(const T s) const { return Vector3{ x + s, y + s, z + s }; }
		constexpr Vector3 operator-(const T s) const { return Vector3{ x - s, y - s, z - s }; }
		constexpr Vector3 operator*(const T s) const { return Vector3{ x * s, y * s, z * s }; }
		constexpr Vector3 operator/(const T s) const { return Vector3{ x / s, y / s, z / s }; }

		constexpr bool operator==(const Vector3& other) const { return x == other.x && y == other.y && z == other.z; }
		constexpr bool operator!=(const Vector3& other) const { return !(*this == other); }

		constexpr T LengthSq() const noexcept{
			return x * x + y * y + z * z;
		}

		T Length() const noexcept{
			if constexpr (std::is_floating_point_v<T>) {
				return std::hypot(x,y,z);
			}
			else {
				return static_cast<T>(std::sqrt(static_cast<double>(LengthSq())));
			}
		};


		constexpr Vector3 Normalize() const requires std::is_floating_point_v<T> {
			T len = Length();
			SPY_CORE_ASSERT(len > 0, "Length is 0!");
			return Vector3{ x / len, y / len, z / len };
		};
	};
}