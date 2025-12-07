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

#define SP_CREATE_FUNC(type) \
	static std::unique_ptr<type> Create(){ return std::make_unique<type>();}

#define SP_MOVE(type) std::move(type)

#define SP_CREATE_MOVE(type) std::move(std::make_unique<type>())

#define SP_STRINGIFY(x) #x

#define SP_BIND_EVENT_FUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); } 

#define SP_IS_SAME_TYPE(target, type) typeid(*target) == typeid(type)