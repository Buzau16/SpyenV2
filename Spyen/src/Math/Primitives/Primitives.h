#pragma once
#include <Math/Vector/Vec.h>

namespace Spyen {
	struct Rectangle {
		Vec2 Position = { 0,0 };
		Vec2 Scale = { 0, 0 }; // is used a a half scale, the anchor point is the middle
		float Rotation = 0.f;

		constexpr Rectangle() = default;
		constexpr Rectangle(const Vec2& position, const Vec2& scale, const float rotation) :
			Position(position), Scale(scale / 2), Rotation(rotation) {}
		constexpr ~Rectangle() = default;
	};

	struct Square {
		Vec2 Position = { 0,0 };
		float Scale = 0.f; // the anchor point is the middle
		float Rotation = 0.f;

		constexpr Square() = default;
		constexpr Square(const Vec2& position, const float scale, const float rotation) :
			Position(position), Scale(scale / 2), Rotation(rotation) {
		}
		constexpr ~Square() = default;
	};
}