#pragma once

#include <memory>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Spyen {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define SPY_CORE_TRACE(...)    ::Spyen::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SPY_CORE_INFO(...)     ::Spyen::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SPY_CORE_WARN(...)     ::Spyen::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SPY_CORE_ERROR(...)    ::Spyen::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SPY_CORE_CRITICAL(...) ::Spyen::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SPY_HZ_TRACE(...)         ::Spyen::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SPY_HZ_INFO(...)          ::Spyen::Log::GetClientLogger()->info(__VA_ARGS__)
#define SPY_HZ_WARN(...)          ::Spyen::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SPY_HZ_ERROR(...)         ::Spyen::Log::GetClientLogger()->error(__VA_ARGS__)
#define SPY_HZ_CRITICAL(...)      ::Spyen::Log::GetClientLogger()->critical(__VA_ARGS__)

#pragma warning(pop)