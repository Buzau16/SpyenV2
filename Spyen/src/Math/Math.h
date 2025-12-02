#pragma once
#include <array>
#include <utility>
#include <Math/glm/glm.hpp>

namespace Spyen
{	
	struct Vec2 {
		float x, y;

		constexpr Vec2(float X, float Y) : x(X), y(Y) {};
		constexpr Vec2(float XY) : x(XY), y(XY) {};

		constexpr Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y;	return *this; }
		constexpr Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y;	return *this; }
		constexpr Vec2& operator*=(const Vec2& other) { x *= other.x; y *= other.y;	return *this; }
		constexpr Vec2& operator/=(const Vec2& other) {	x /= other.x; y /= other.y;	return *this; }

		constexpr Vec2& operator+=(const float s) { x += s; y += s;	return *this; }
		constexpr Vec2& operator-=(const float s) { x -= s; y -= s;	return *this; }
		constexpr Vec2& operator*=(const float s) { x *= s; y *= s;	return *this; }
		constexpr Vec2& operator/=(const float s) { x /= s; y /= s;	return *this; }

		constexpr Vec2 operator+(const Vec2& other) const { return Vec2{ x + other.x, y + other.y }; }
		constexpr Vec2 operator-(const Vec2& other) const { return Vec2{ x - other.x, y - other.y }; }
		constexpr Vec2 operator*(const Vec2& other) const { return Vec2{ x * other.x, y * other.y }; }
		constexpr Vec2 operator/(const Vec2& other) const { return Vec2{ x / other.x, y / other.y }; }

		constexpr Vec2 operator+(const float s) const { return Vec2{ x + s, y + s }; }
		constexpr Vec2 operator-(const float s) const { return Vec2{ x - s, y - s }; }
		constexpr Vec2 operator*(const float s) const { return Vec2{ x * s, y * s }; }
		constexpr Vec2 operator/(const float s) const { return Vec2{ x / s, y / s }; }

		constexpr bool operator==(const Vec2& o) const { return x == o.x && y == o.y; }
		constexpr bool operator!=(const Vec2& o) const { return !(*this == o); }

		inline float Length() const { return std::hypot(x, y); };
		inline Vec2 Normalize() { return Vec2{ x / Length(), y / Length() }; };
		inline Vec2 Normalize() const { return Vec2{ x / Length(), y / Length() }; };
	};

	struct IVec2 {
		uint64_t x, y;

		constexpr IVec2(uint64_t X, uint64_t Y) : x(X), y(Y) {};
		constexpr IVec2(uint64_t XY) : x(XY), y(XY) {};

		constexpr IVec2& operator+=(const IVec2& other) { x += other.x; y += other.y;	return *this; }
		constexpr IVec2& operator-=(const IVec2& other) { x -= other.x; y -= other.y;	return *this; }
		constexpr IVec2& operator*=(const IVec2& other) { x *= other.x; y *= other.y;	return *this; }
		constexpr IVec2& operator/=(const IVec2& other) { x /= other.x; y /= other.y;	return *this; }

		constexpr IVec2& operator+=(const uint64_t s) { x += s; y += s;	return *this; }
		constexpr IVec2& operator-=(const uint64_t s) { x -= s; y -= s;	return *this; }
		constexpr IVec2& operator*=(const uint64_t s) { x *= s; y *= s;	return *this; }
		constexpr IVec2& operator/=(const uint64_t s) { x /= s; y /= s;	return *this; }

		constexpr IVec2 operator+(const IVec2& other) const { return IVec2{ x + other.x, y + other.y }; }
		constexpr IVec2 operator-(const IVec2& other) const { return IVec2{ x - other.x, y - other.y }; }
		constexpr IVec2 operator*(const IVec2& other) const { return IVec2{ x * other.x, y * other.y }; }
		constexpr IVec2 operator/(const IVec2& other) const { return IVec2{ x / other.x, y / other.y }; }

		constexpr IVec2 operator+(const uint64_t s) const { return IVec2{ x + s, y + s }; }
		constexpr IVec2 operator-(const uint64_t s) const { return IVec2{ x - s, y - s }; }
		constexpr IVec2 operator*(const uint64_t s) const { return IVec2{ x * s, y * s }; }
		constexpr IVec2 operator/(const uint64_t s) const { return IVec2{ x / s, y / s }; }

		constexpr bool operator==(const IVec2& o) const { return x == o.x && y == o.y; }
		constexpr bool operator!=(const IVec2& o) const { return !(*this == o); }

		inline uint64_t Length() const { return std::hypot(x, y); };
		inline IVec2 Normalize() { return IVec2{ x / Length(), y / Length() }; };
		inline IVec2 Normalize() const { return IVec2{ x / Length(), y / Length() }; };
	};

	struct Vec3 {
		float x, y, z;

		constexpr Vec3() : x(0), y(0), z(0) {};
		constexpr Vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) {};
		constexpr Vec3(float XYZ) : x(XYZ), y(XYZ), z(XYZ) {};

		constexpr Vec3& operator+=(const Vec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
		constexpr Vec3& operator-=(const Vec3& other) { x -= other.x; y -= other.y;	z -= other.z; return *this; }
		constexpr Vec3& operator*=(const Vec3& other) { x *= other.x; y *= other.y;	z *= other.z; return *this; }
		constexpr Vec3& operator/=(const Vec3& other) { x /= other.x; y /= other.y;	z /= other.z; return *this; }

		constexpr Vec3& operator+=(const float s) { x += s; y += s;	z += s; return *this; }
		constexpr Vec3& operator-=(const float s) { x -= s; y -= s;	z -= s; return *this; }
		constexpr Vec3& operator*=(const float s) { x *= s; y *= s;	z *= s; return *this; }
		constexpr Vec3& operator/=(const float s) { x /= s; y /= s;	z /= s; return *this; }

		constexpr Vec3 operator+(const Vec3& other) const { return Vec3{ x + other.x, y + other.y, z + other.z }; }
		constexpr Vec3 operator-(const Vec3& other) const { return Vec3{ x - other.x, y - other.y, z - other.z }; }
		constexpr Vec3 operator*(const Vec3& other) const { return Vec3{ x * other.x, y * other.y, z * other.z }; }
		constexpr Vec3 operator/(const Vec3& other) const { return Vec3{ x / other.x, y / other.y, z / other.z }; }

		constexpr Vec3 operator+(const float s) const { return Vec3{ x + s, y + s, z + s }; }
		constexpr Vec3 operator-(const float s) const { return Vec3{ x - s, y - s, z - s }; }
		constexpr Vec3 operator*(const float s) const { return Vec3{ x * s, y * s, z * s }; }
		constexpr Vec3 operator/(const float s) const { return Vec3{ x / s, y / s, z / s }; }

		constexpr bool operator==(const Vec3& other) const { return x == other.x && y == other.y && z == other.z; }
		constexpr bool operator!=(const Vec3& other) const { return !(*this == other); }

		inline float Length() const { return std::hypot(x, y, z); };
		inline Vec3 Normalize() { auto len = Length(); return Vec3{ x / len, y / len, z / len }; };
		inline Vec3 Normalize() const { auto len = Length(); return Vec3{ x / len, y / len, z / len }; };
	};

	struct IVec3 {
		uint64_t x, y, z;

		constexpr IVec3(uint64_t X, uint64_t Y, uint64_t Z) : x(X), y(Y), z(Z) {};
		constexpr IVec3(uint64_t XYZ) : x(XYZ), y(XYZ), z(XYZ) {};

		constexpr IVec3& operator+=(const IVec3& other) { x += other.x; y += other.y; z += other.z; return *this; }
		constexpr IVec3& operator-=(const IVec3& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
		constexpr IVec3& operator*=(const IVec3& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
		constexpr IVec3& operator/=(const IVec3& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

		constexpr IVec3& operator+=(const uint64_t s) { x += s; y += s;	z += s; return *this; }
		constexpr IVec3& operator-=(const uint64_t s) { x -= s; y -= s;	z -= s; return *this; }
		constexpr IVec3& operator*=(const uint64_t s) { x *= s; y *= s;	z *= s; return *this; }
		constexpr IVec3& operator/=(const uint64_t s) { x /= s; y /= s;	z /= s; return *this; }

		constexpr IVec3 operator+(const IVec3& other) const { return IVec3{ x + other.x, y + other.y, z + other.z }; }
		constexpr IVec3 operator-(const IVec3& other) const { return IVec3{ x - other.x, y - other.y, z - other.z }; }
		constexpr IVec3 operator*(const IVec3& other) const { return IVec3{ x * other.x, y * other.y, z * other.z }; }
		constexpr IVec3 operator/(const IVec3& other) const { return IVec3{ x / other.x, y / other.y, z / other.z }; }

		constexpr IVec3 operator+(const uint64_t s) const { return IVec3{ x + s, y + s, z + s }; }
		constexpr IVec3 operator-(const uint64_t s) const { return IVec3{ x - s, y - s, z - s }; }
		constexpr IVec3 operator*(const uint64_t s) const { return IVec3{ x * s, y * s, z * s }; }
		constexpr IVec3 operator/(const uint64_t s) const { return IVec3{ x / s, y / s, z / s }; }

		constexpr bool operator==(const IVec3& other) const { return x == other.x && y == other.y && z == other.z; }
		constexpr bool operator!=(const IVec3& other) const { return !(*this == other); }

		inline uint64_t Length() const { return std::hypot(x, y, z); };
		inline IVec3 Normalize() { auto len = Length(); return IVec3{ x / len, y / len, z / len }; };
		inline IVec3 Normalize() const { auto len = Length(); return IVec3{ x / len, y / len, z / len }; };
	};

	struct OBB;

	namespace Math
	{
		glm::vec2 ToGLMVec2(const Vec2& v);
		glm::vec3 ToGLMVec3(const Vec3& v);
		glm::ivec2 ToGLMIVec2(const IVec2& v);
		glm::ivec3 ToGLMIVec3(const IVec3& v);

		constexpr float Dot(const Vec2& a, const Vec2& b){ return a.x * b.x + a.y * b.y; }
		constexpr float Dot(const Vec3& a, const Vec3& b){ return a.x * b.x + a.y * b.y + a.z * b.z; }
		constexpr float Dot(const IVec2& a, const IVec2& b){ return a.x * b.x + a.y * b.y; }
		constexpr float Dot(const IVec3& a, const IVec3& b){ return a.x * b.x + a.y * b.y + a.z * b.z; }

		std::pair<float, float> Project(const OBB& box, const Vec2& axis);
		bool IsColliding(const OBB& a, const OBB& b);
	}
}
