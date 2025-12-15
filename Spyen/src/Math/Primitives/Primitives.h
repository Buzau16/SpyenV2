#pragma once
#include <Math/Vector/Vec.h>

namespace Spyen {
	struct Rectangle {
		Vec2 Position = { 0,0 };
		Vec2 Scale = { 0, 0 }; // Half size, the anchor point being the middle of the rect
		float Rotation = 0.f;

		constexpr Rectangle() = default;
		constexpr Rectangle(const Vec2& position, const Vec2& scale, const float rotation) :
			Position(position), Scale(scale / 2), Rotation(rotation) {}
		constexpr ~Rectangle() = default;

		inline Vec2 GetMin() const {
			if (Rotation == 0.f) {
				return Vec2{ Position - Scale };
			}
			const auto c = std::cos(Rotation);
			const auto s = std::sin(Rotation);

			const auto ex = Scale.x;
			const auto ey = Scale.y;

			const auto px = std::abs(ex * c) + std::abs(ey * -s);
			const auto py = std::abs(ex * s) + std::abs(ey * c);

			return Vec2{Position.x - px, Position.y - py};
		}

		inline Vec2 GetMax() const {
			if (Rotation == 0.f) {
				return Vec2{ Position + Scale };
			}
			const auto c = std::cos(Rotation);
			const auto s = std::sin(Rotation);

			const auto ex = Scale.x;
			const auto ey = Scale.y;

			const auto px = std::abs(ex * c) + std::abs(ey * -s);
			const auto py = std::abs(ex * s) + std::abs(ey * c);

			return Vec2{ Position.x + px, Position.y + py };
		}
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