#pragma once
#include <type_traits>
#include <random>

namespace Spyen {
	namespace Math {
		static std::random_device s_RandomDevice;
		static std::mt19937_64 s_Engine(s_RandomDevice());

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr T Min(const T& a, const T& b) {
			return a < b ? a : b;
		}

		template<typename T>
			requires std::is_arithmetic_v<T>
		constexpr T Max(const T& a, const T& b) {
			return a > b ? a : b;
		}

		template<typename T>
		requires std::is_arithmetic_v<T>
		T Random(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
			if constexpr (std::is_integral_v<T>) {
				std::uniform_int_distribution<T> dist(min, max);
				return dist(s_Engine);
			}
			else if constexpr (std::is_floating_point_v<T>) {
				std::uniform_real_distribution<T> dist(min, max);
				return dist(s_Engine);
			}
		}

	}
}