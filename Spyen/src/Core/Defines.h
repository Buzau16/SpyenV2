#pragma once

#ifdef _WIN64
	#define SP_PLATFORM_WINDOWS
#elif defined(_WIN32)
	#error "x86 builds are not supported!"
#elif defined(__linux__)
	#define SP_PLATFORM_LINUX
#elif
	#error "Platform not supported!"
#endif


// To be used only in the Spyen source Code
#define SP_BIT(x) (1 << x)

// Can be used by the user
// everything here is part of the old scene system, try to avoid!
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

// add script is modified from using a unique ptr for now
#define SP_ADD_SCRIPT(entity, script) entity.AddComponent<Spyen::ScriptComponent>().ScriptInstance = new script;

#if defined(_MSC_VER)
	#define SP_DEBUGBRAKE() __debugbrake()
#elif defined(__GNUC__) || defined(__clang__)
	#define SP_DEBUGBRAKE() __builtin_trap()
#endif
