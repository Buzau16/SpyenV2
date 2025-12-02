#pragma once

#ifdef SP_DEBUG
#define SPY_ASSERT(x, ...) { if(!(x)) { SPY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define SPY_CORE_ASSERT(x, ...) { if(!(x)) { SPY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define SPY_ASSERT(x, ...) x
#define SPY_CORE_ASSERT(x, ...) x
#endif

#define SP_SYNTHESIZE(type, name, func) \
	constexpr type Get##func() const noexcept { return name; }\
	inline void Set##func(const type& value) noexcept { name = value; }

#define SP_SYNTHESIZE_NR(type, name, func) \
	constexpr type Get##func() const noexcept { return name; }\
	inline void Set##func(const type value) noexcept { name = value; }

#define SP_AS(var, type) \
	dynamic_cast<type*>(var)